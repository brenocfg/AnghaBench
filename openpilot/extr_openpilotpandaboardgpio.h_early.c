#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_12__ {unsigned int IDCODE; } ;
struct TYPE_11__ {scalar_t__ PUPDR; scalar_t__ ODR; scalar_t__ MODER; } ;
struct TYPE_10__ {scalar_t__ PUPDR; scalar_t__ ODR; scalar_t__ MODER; } ;
struct TYPE_9__ {scalar_t__ PUPDR; scalar_t__ ODR; scalar_t__ MODER; } ;
struct TYPE_8__ {int AHB1ENR; } ;
struct TYPE_7__ {scalar_t__ VTOR; } ;

/* Variables and functions */
 scalar_t__ BOOT_NORMAL ; 
 TYPE_6__* DBGMCU ; 
 scalar_t__ ENTER_BOOTLOADER_MAGIC ; 
 scalar_t__ ENTER_SOFTLOADER_MAGIC ; 
 TYPE_5__* GPIOA ; 
 TYPE_4__* GPIOB ; 
 TYPE_3__* GPIOC ; 
 int /*<<< orphan*/  LED_GREEN ; 
 int /*<<< orphan*/  NVIC_SystemReset () ; 
 TYPE_2__* RCC ; 
 int RCC_AHB1ENR_GPIOAEN ; 
 int RCC_AHB1ENR_GPIOBEN ; 
 int RCC_AHB1ENR_GPIOCEN ; 
 TYPE_1__* SCB ; 
 int /*<<< orphan*/  detect () ; 
 scalar_t__ enter_bootloader_mode ; 
 int /*<<< orphan*/  g_pfnVectors ; 
 scalar_t__ is_entering_bootmode ; 
 int /*<<< orphan*/  jump_to_bootloader () ; 
 int /*<<< orphan*/  set_led (int /*<<< orphan*/ ,int) ; 

void early() {
  // after it's been in the bootloader, things are initted differently, so we reset
  if (enter_bootloader_mode != BOOT_NORMAL &&
      enter_bootloader_mode != ENTER_BOOTLOADER_MAGIC &&
      enter_bootloader_mode != ENTER_SOFTLOADER_MAGIC) {
    enter_bootloader_mode = BOOT_NORMAL;
    NVIC_SystemReset();
  }

  // if wrong chip, reboot
  volatile unsigned int id = DBGMCU->IDCODE;
  #ifdef STM32F4
    if ((id&0xFFF) != 0x463) enter_bootloader_mode = ENTER_BOOTLOADER_MAGIC;
  #else
    if ((id&0xFFF) != 0x411) enter_bootloader_mode = ENTER_BOOTLOADER_MAGIC;
  #endif

  // setup interrupt table
  SCB->VTOR = (uint32_t)&g_pfnVectors;

  // early GPIOs float everything
  RCC->AHB1ENR = RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;

  GPIOA->MODER = 0; GPIOB->MODER = 0; GPIOC->MODER = 0;
  GPIOA->ODR = 0; GPIOB->ODR = 0; GPIOC->ODR = 0;
  GPIOA->PUPDR = 0; GPIOB->PUPDR = 0; GPIOC->PUPDR = 0;

  detect();

  #ifdef PANDA
    // enable the ESP, disable ESP boot mode
    // unless we are on a giant panda, then there's no ESP
    // dont disable on grey panda
    if (is_giant_panda) {
      set_esp_mode(ESP_DISABLED);
    } else {
      set_esp_mode(ESP_ENABLED);
    }
  #endif


  if (enter_bootloader_mode == ENTER_BOOTLOADER_MAGIC) {
  #ifdef PANDA
    set_esp_mode(ESP_DISABLED);
  #endif
    set_led(LED_GREEN, 1);
    jump_to_bootloader();
  }

  if (is_entering_bootmode) {
    enter_bootloader_mode = ENTER_SOFTLOADER_MAGIC;
  }
}