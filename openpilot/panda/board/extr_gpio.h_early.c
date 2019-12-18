#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_14__ {unsigned int IDCODE; } ;
struct TYPE_13__ {scalar_t__ PUPDR; scalar_t__ ODR; scalar_t__ MODER; } ;
struct TYPE_12__ {scalar_t__ PUPDR; scalar_t__ ODR; scalar_t__ MODER; } ;
struct TYPE_11__ {scalar_t__ PUPDR; scalar_t__ ODR; scalar_t__ MODER; } ;
struct TYPE_10__ {int AHB1ENR; } ;
struct TYPE_9__ {scalar_t__ VTOR; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* set_led ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* set_esp_gps_mode ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ BOOT_NORMAL ; 
 TYPE_7__* DBGMCU ; 
 scalar_t__ ENTER_BOOTLOADER_MAGIC ; 
 scalar_t__ ENTER_SOFTLOADER_MAGIC ; 
 int /*<<< orphan*/  ESP_GPS_DISABLED ; 
 int /*<<< orphan*/  ESP_GPS_ENABLED ; 
 TYPE_6__* GPIOA ; 
 TYPE_5__* GPIOB ; 
 TYPE_4__* GPIOC ; 
 int /*<<< orphan*/  LED_GREEN ; 
 int /*<<< orphan*/  NVIC_SystemReset () ; 
 TYPE_3__* RCC ; 
 int RCC_AHB1ENR_GPIOAEN ; 
 int RCC_AHB1ENR_GPIOBEN ; 
 int RCC_AHB1ENR_GPIOCEN ; 
 TYPE_2__* SCB ; 
 TYPE_1__* current_board ; 
 int /*<<< orphan*/  detect_board_type () ; 
 int /*<<< orphan*/  detect_configuration () ; 
 int /*<<< orphan*/  enable_interrupts () ; 
 scalar_t__ enter_bootloader_mode ; 
 int /*<<< orphan*/  g_pfnVectors ; 
 scalar_t__ global_critical_depth ; 
 scalar_t__ is_entering_bootmode ; 
 int /*<<< orphan*/  jump_to_bootloader () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int) ; 

void early(void) {
  // Reset global critical depth
  global_critical_depth = 0;

  // neccesary for DFU flashing on a non-power cycled white panda
  enable_interrupts();

  // after it's been in the bootloader, things are initted differently, so we reset
  if ((enter_bootloader_mode != BOOT_NORMAL) &&
      (enter_bootloader_mode != ENTER_BOOTLOADER_MAGIC) &&
      (enter_bootloader_mode != ENTER_SOFTLOADER_MAGIC)) {
    enter_bootloader_mode = BOOT_NORMAL;
    NVIC_SystemReset();
  }

  // if wrong chip, reboot
  volatile unsigned int id = DBGMCU->IDCODE;
  #ifdef STM32F4
    if ((id & 0xFFFU) != 0x463U) {
      enter_bootloader_mode = ENTER_BOOTLOADER_MAGIC;
    }
  #else
    if ((id & 0xFFFU) != 0x411U) {
      enter_bootloader_mode = ENTER_BOOTLOADER_MAGIC;
    }
  #endif

  // setup interrupt table
  SCB->VTOR = (uint32_t)&g_pfnVectors;

  // early GPIOs float everything
  RCC->AHB1ENR = RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;

  GPIOA->MODER = 0; GPIOB->MODER = 0; GPIOC->MODER = 0;
  GPIOA->ODR = 0; GPIOB->ODR = 0; GPIOC->ODR = 0;
  GPIOA->PUPDR = 0; GPIOB->PUPDR = 0; GPIOC->PUPDR = 0;

  detect_configuration();
  detect_board_type();

  #ifdef PANDA
    // enable the ESP, disable ESP boot mode
    // dont disable on grey panda
    current_board->set_esp_gps_mode(ESP_GPS_ENABLED);
  #endif


  if (enter_bootloader_mode == ENTER_BOOTLOADER_MAGIC) {
  #ifdef PANDA
    current_board->set_esp_gps_mode(ESP_GPS_DISABLED);
  #endif
    current_board->set_led(LED_GREEN, 1);
    jump_to_bootloader();
  }

  if (is_entering_bootmode) {
    enter_bootloader_mode = ENTER_SOFTLOADER_MAGIC;
  }
}