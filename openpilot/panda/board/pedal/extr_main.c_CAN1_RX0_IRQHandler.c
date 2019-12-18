#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  unsigned int uint16_t ;
struct TYPE_6__ {int RF0R; TYPE_1__* sFIFOMailBox; } ;
struct TYPE_5__ {int RIR; } ;

/* Variables and functions */
 TYPE_4__* CAN ; 
 int CAN_GAS_INPUT ; 
 scalar_t__ CAN_GAS_SIZE ; 
 int CAN_RF0R_FMP0 ; 
 int CAN_RF0R_RFOM0 ; 
 int COUNTER_CYCLE ; 
 int /*<<< orphan*/  ENTER_BOOTLOADER_MAGIC ; 
 int /*<<< orphan*/  ENTER_SOFTLOADER_MAGIC ; 
 int /*<<< orphan*/  FAULT_BAD_CHECKSUM ; 
 int /*<<< orphan*/  FAULT_INVALID ; 
 int GET_BYTE (TYPE_1__*,int) ; 
 int GET_BYTES_04 (TYPE_1__*) ; 
 int GET_BYTES_48 (TYPE_1__*) ; 
 int /*<<< orphan*/  NO_FAULT ; 
 int /*<<< orphan*/  NVIC_SystemReset () ; 
 unsigned int current_index ; 
 int /*<<< orphan*/  enter_bootloader_mode ; 
 unsigned int gas_set_0 ; 
 unsigned int gas_set_1 ; 
 int pedal_checksum (int*,scalar_t__) ; 
 int /*<<< orphan*/  puth (unsigned int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  state ; 
 scalar_t__ timeout ; 

void CAN1_RX0_IRQHandler(void) {
  while ((CAN->RF0R & CAN_RF0R_FMP0) != 0) {
    #ifdef DEBUG
      puts("CAN RX\n");
    #endif
    int address = CAN->sFIFOMailBox[0].RIR >> 21;
    if (address == CAN_GAS_INPUT) {
      // softloader entry
      if (GET_BYTES_04(&CAN->sFIFOMailBox[0]) == 0xdeadface) {
        if (GET_BYTES_48(&CAN->sFIFOMailBox[0]) == 0x0ab00b1e) {
          enter_bootloader_mode = ENTER_SOFTLOADER_MAGIC;
          NVIC_SystemReset();
        } else if (GET_BYTES_48(&CAN->sFIFOMailBox[0]) == 0x02b00b1e) {
          enter_bootloader_mode = ENTER_BOOTLOADER_MAGIC;
          NVIC_SystemReset();
        } else {
          puts("Failed entering Softloader or Bootloader\n");
        }
      }

      // normal packet
      uint8_t dat[8];
      for (int i=0; i<8; i++) {
        dat[i] = GET_BYTE(&CAN->sFIFOMailBox[0], i);
      }
      uint16_t value_0 = (dat[0] << 8) | dat[1];
      uint16_t value_1 = (dat[2] << 8) | dat[3];
      bool enable = ((dat[4] >> 7) & 1U) != 0U;
      uint8_t index = dat[4] & COUNTER_CYCLE;
      if (pedal_checksum(dat, CAN_GAS_SIZE - 1) == dat[5]) {
        if (((current_index + 1U) & COUNTER_CYCLE) == index) {
          #ifdef DEBUG
            puts("setting gas ");
            puth(value_0);
            puts("\n");
          #endif
          if (enable) {
            gas_set_0 = value_0;
            gas_set_1 = value_1;
          } else {
            // clear the fault state if values are 0
            if ((value_0 == 0U) && (value_1 == 0U)) {
              state = NO_FAULT;
            } else {
              state = FAULT_INVALID;
            }
            gas_set_0 = 0;
            gas_set_1 = 0;
          }
          // clear the timeout
          timeout = 0;
        }
        current_index = index;
      } else {
        // wrong checksum = fault
        state = FAULT_BAD_CHECKSUM;
      }
    }
    // next
    CAN->RF0R |= CAN_RF0R_RFOM0;
  }
}