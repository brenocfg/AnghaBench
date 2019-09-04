#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int RF0R; TYPE_1__* sFIFOMailBox; } ;
struct TYPE_3__ {int RIR; int RDLR; int RDHR; } ;

/* Variables and functions */
 TYPE_2__* CAN ; 
 scalar_t__ CAN_GAS_INPUT ; 
 scalar_t__ CAN_GAS_SIZE ; 
 int CAN_RF0R_FMP0 ; 
 int CAN_RF0R_RFOM0 ; 
 int COUNTER_CYCLE ; 
 int /*<<< orphan*/  ENTER_BOOTLOADER_MAGIC ; 
 int /*<<< orphan*/  ENTER_SOFTLOADER_MAGIC ; 
 int /*<<< orphan*/  FAULT_BAD_CHECKSUM ; 
 int /*<<< orphan*/  FAULT_INVALID ; 
 int /*<<< orphan*/  NO_FAULT ; 
 int /*<<< orphan*/  NVIC_SystemReset () ; 
 int current_index ; 
 int /*<<< orphan*/  enter_bootloader_mode ; 
 scalar_t__ gas_set_0 ; 
 scalar_t__ gas_set_1 ; 
 int pedal_checksum (int*,scalar_t__) ; 
 int /*<<< orphan*/  state ; 
 scalar_t__ timeout ; 

void CAN1_RX0_IRQHandler() {
  while (CAN->RF0R & CAN_RF0R_FMP0) {
    #ifdef DEBUG
      puts("CAN RX\n");
    #endif
    uint32_t address = CAN->sFIFOMailBox[0].RIR>>21;
    if (address == CAN_GAS_INPUT) {
      // softloader entry
      if (CAN->sFIFOMailBox[0].RDLR == 0xdeadface) {
        if (CAN->sFIFOMailBox[0].RDHR == 0x0ab00b1e) {
          enter_bootloader_mode = ENTER_SOFTLOADER_MAGIC;
          NVIC_SystemReset();
        } else if (CAN->sFIFOMailBox[0].RDHR == 0x02b00b1e) {
          enter_bootloader_mode = ENTER_BOOTLOADER_MAGIC;
          NVIC_SystemReset();
        }
      }

      // normal packet
      uint8_t dat[8];
      uint8_t *rdlr = (uint8_t *)&CAN->sFIFOMailBox[0].RDLR;
      uint8_t *rdhr = (uint8_t *)&CAN->sFIFOMailBox[0].RDHR;
      for (int i=0; i<4; i++) {
        dat[i] = rdlr[i];
        dat[i+4] = rdhr[i];
      }
      uint16_t value_0 = (dat[0] << 8) | dat[1];
      uint16_t value_1 = (dat[2] << 8) | dat[3];
      uint8_t enable = (dat[4] >> 7) & 1;
      uint8_t index = dat[4] & COUNTER_CYCLE;
      if (pedal_checksum(dat, CAN_GAS_SIZE - 1) == dat[5]) {
        if (((current_index + 1) & COUNTER_CYCLE) == index) {
          #ifdef DEBUG
            puts("setting gas ");
            puth(value);
            puts("\n");
          #endif
          if (enable) {
            gas_set_0 = value_0;
            gas_set_1 = value_1;
          } else {
            // clear the fault state if values are 0
            if (value_0 == 0 && value_1 == 0) {
              state = NO_FAULT;
            } else {
              state = FAULT_INVALID;
            }
            gas_set_0 = gas_set_1 = 0;
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