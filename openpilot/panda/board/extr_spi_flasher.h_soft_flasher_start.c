#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  APB1ENR; int /*<<< orphan*/  AHB2ENR; int /*<<< orphan*/  APB2ENR; int /*<<< orphan*/  AHB1ENR; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* set_led ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* set_usb_power_mode ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* enable_can_transciever ) (int,int) ;} ;
struct TYPE_6__ {int OSPEEDR; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN1 ; 
 TYPE_1__* GPIOA ; 
 TYPE_1__* GPIOB ; 
 int /*<<< orphan*/  GPIO_AF10_OTG_FS ; 
 int /*<<< orphan*/  GPIO_AF5_SPI1 ; 
 int /*<<< orphan*/  GPIO_AF7_USART2 ; 
 int /*<<< orphan*/  GPIO_AF9_CAN1 ; 
 int GPIO_OSPEEDER_OSPEEDR11 ; 
 int GPIO_OSPEEDER_OSPEEDR12 ; 
 int /*<<< orphan*/  LED_BLUE ; 
 int /*<<< orphan*/  LED_GREEN ; 
 TYPE_3__* RCC ; 
 int /*<<< orphan*/  RCC_AHB1ENR_DMA2EN ; 
 int /*<<< orphan*/  RCC_AHB2ENR_OTGFSEN ; 
 int /*<<< orphan*/  RCC_APB1ENR_CAN1EN ; 
 int /*<<< orphan*/  RCC_APB1ENR_USART2EN ; 
 int /*<<< orphan*/  RCC_APB2ENR_SPI1EN ; 
 int /*<<< orphan*/  USB_POWER_CDP ; 
 scalar_t__ USB_POWER_CLIENT ; 
 TYPE_2__* current_board ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  enable_interrupts () ; 
 scalar_t__ enter_bootloader_mode ; 
 int /*<<< orphan*/  is_enumerated ; 
 int /*<<< orphan*/  llcan_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  llcan_set_speed (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  set_gpio_alternate (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_init () ; 
 int /*<<< orphan*/  stub1 (int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_init () ; 
 scalar_t__ usb_power_mode ; 

void soft_flasher_start(void) {
  puts("\n\n\n************************ FLASHER START ************************\n");

  enter_bootloader_mode = 0;

  RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
  RCC->AHB2ENR |= RCC_AHB2ENR_OTGFSEN;
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

// pedal has the canloader
#ifdef PEDAL
  RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;

  // B8,B9: CAN 1
  set_gpio_alternate(GPIOB, 8, GPIO_AF9_CAN1);
  set_gpio_alternate(GPIOB, 9, GPIO_AF9_CAN1);
  current_board->enable_can_transciever(1, true);

  // init can
  llcan_set_speed(CAN1, 5000, false, false);
  llcan_init(CAN1);
#endif

  // A4,A5,A6,A7: setup SPI
  set_gpio_alternate(GPIOA, 4, GPIO_AF5_SPI1);
  set_gpio_alternate(GPIOA, 5, GPIO_AF5_SPI1);
  set_gpio_alternate(GPIOA, 6, GPIO_AF5_SPI1);
  set_gpio_alternate(GPIOA, 7, GPIO_AF5_SPI1);

  // A2,A3: USART 2 for debugging
  set_gpio_alternate(GPIOA, 2, GPIO_AF7_USART2);
  set_gpio_alternate(GPIOA, 3, GPIO_AF7_USART2);

  // A11,A12: USB
  set_gpio_alternate(GPIOA, 11, GPIO_AF10_OTG_FS);
  set_gpio_alternate(GPIOA, 12, GPIO_AF10_OTG_FS);
  GPIOA->OSPEEDR = GPIO_OSPEEDER_OSPEEDR11 | GPIO_OSPEEDER_OSPEEDR12;

  // flasher
  spi_init();

  // enable USB
  usb_init();

  // green LED on for flashing
  current_board->set_led(LED_GREEN, 1);

  enable_interrupts();

  uint64_t cnt = 0;

  for (cnt=0;;cnt++) {
    if (cnt == 35 && !is_enumerated && usb_power_mode == USB_POWER_CLIENT) {
      // if you are connected through a hub to the phone
      // you need power to be able to see the device
      puts("USBP: didn't enumerate, switching to CDP mode\n");
      current_board->set_usb_power_mode(USB_POWER_CDP);
      current_board->set_led(LED_BLUE, 1);
    }
    // blink the green LED fast
    current_board->set_led(LED_GREEN, 0);
    delay(500000);
    current_board->set_led(LED_GREEN, 1);
    delay(500000);
  }
}