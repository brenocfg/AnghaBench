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
typedef  int uint64_t ;
struct TYPE_4__ {int IER; } ;
struct TYPE_3__ {int PSC; int /*<<< orphan*/  EGR; int /*<<< orphan*/  CR1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_CAN_SILENT ; 
 TYPE_2__* CAN1 ; 
 int CAN_IER_ERRIE ; 
 int CAN_IER_LECIE ; 
 int /*<<< orphan*/  LED_GREEN ; 
 int /*<<< orphan*/  LED_RED ; 
 int /*<<< orphan*/  SAFETY_NOOUTPUT ; 
 TYPE_1__* TIM2 ; 
 int /*<<< orphan*/  TIM_CR1_CEN ; 
 int /*<<< orphan*/  TIM_EGR_UG ; 
 int /*<<< orphan*/  USART2 ; 
 scalar_t__ USB_POWER_DCP ; 
 int /*<<< orphan*/  __disable_irq () ; 
 int /*<<< orphan*/  __enable_irq () ; 
 int /*<<< orphan*/  adc_init () ; 
 int /*<<< orphan*/  can_init_all () ; 
 scalar_t__ can_live ; 
 int /*<<< orphan*/  can_silent ; 
 int /*<<< orphan*/  clock_init () ; 
 int controls_allowed ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  detect () ; 
 int /*<<< orphan*/  fan_init () ; 
 int /*<<< orphan*/  fan_set_speed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_init () ; 
 scalar_t__ has_external_debug_serial ; 
 scalar_t__ is_entering_bootmode ; 
 scalar_t__ is_giant_panda ; 
 scalar_t__ is_grey_panda ; 
 scalar_t__ pending_can_live ; 
 int /*<<< orphan*/  periph_init () ; 
 int /*<<< orphan*/  power_save_init () ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  safety_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_led (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uart_init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_init () ; 
 scalar_t__ usb_power_mode ; 

int main() {
  // shouldn't have interrupts here, but just in case
  __disable_irq();

  // init early devices
  clock_init();
  periph_init();
  detect();

  // print hello
  puts("\n\n\n************************ MAIN START ************************\n");

  // detect the revision and init the GPIOs
  puts("config:\n");
  #ifdef PANDA
    puts(revision == PANDA_REV_C ? "  panda rev c\n" : "  panda rev a or b\n");
  #else
    puts("  legacy\n");
  #endif
  puts(has_external_debug_serial ? "  real serial\n" : "  USB serial\n");
  puts(is_giant_panda ? "  GIANTpanda detected\n" : "  not GIANTpanda\n");
  puts(is_grey_panda ? "  gray panda detected!\n" : "  white panda\n");
  puts(is_entering_bootmode ? "  ESP wants bootmode\n" : "  no bootmode\n");
  gpio_init();

#ifdef PANDA
  // panda has an FPU, let's use it!
  enable_fpu();
#endif

  // enable main uart if it's connected
  if (has_external_debug_serial) {
    // WEIRDNESS: without this gate around the UART, it would "crash", but only if the ESP is enabled
    // assuming it's because the lines were left floating and spurious noise was on them
    uart_init(USART2, 115200);
  }

#ifdef PANDA
  if (is_grey_panda) {
    uart_init(USART1, 9600);
  } else {
    // enable ESP uart
    uart_init(USART1, 115200);
    #ifdef EON
      set_esp_mode(ESP_DISABLED);
    #endif
  }
  // enable LIN
  uart_init(UART5, 10400);
  UART5->CR2 |= USART_CR2_LINEN;
  uart_init(USART3, 10400);
  USART3->CR2 |= USART_CR2_LINEN;
#endif

  // init microsecond system timer
  // increments 1000000 times per second
  // generate an update to set the prescaler
  TIM2->PSC = 48-1;
  TIM2->CR1 = TIM_CR1_CEN;
  TIM2->EGR = TIM_EGR_UG;
  // use TIM2->CNT to read

  // enable USB
  usb_init();

  // default to silent mode to prevent issues with Ford
  // hardcode a specific safety mode if you want to force the panda to be in a specific mode
  safety_set_mode(SAFETY_NOOUTPUT, 0);
  can_silent = ALL_CAN_SILENT;
  can_init_all();

  adc_init();

#ifdef PANDA
  spi_init();
#endif
#ifdef DEBUG
  puts("DEBUG ENABLED\n");
#endif

  // set PWM
  fan_init();
  fan_set_speed(0);

  puts("**** INTERRUPTS ON ****\n");

  __enable_irq();

  power_save_init();

  // if the error interrupt is enabled to quickly when the CAN bus is active
  // something bad happens and you can't connect to the device over USB
  delay(10000000);
  CAN1->IER |= CAN_IER_ERRIE | CAN_IER_LECIE;

  // LED should keep on blinking all the time
  uint64_t cnt = 0;

  #ifdef PANDA
    uint64_t marker = 0;
    #define CURRENT_THRESHOLD 0xF00
    #define CLICKS 8
  #endif

  for (cnt=0;;cnt++) {
    can_live = pending_can_live;

    //puth(usart1_dma); puts(" "); puth(DMA2_Stream5->M0AR); puts(" "); puth(DMA2_Stream5->NDTR); puts("\n");

    #ifdef PANDA
      int current = adc_get(ADCCHAN_CURRENT);

      switch (usb_power_mode) {
        case USB_POWER_CLIENT:
          if ((cnt-marker) >= CLICKS) {
            if (!is_enumerated) {
              puts("USBP: didn't enumerate, switching to CDP mode\n");
              // switch to CDP
              set_usb_power_mode(USB_POWER_CDP);
              marker = cnt;
            }
          }
          // keep resetting the timer if it's enumerated
          if (is_enumerated) {
            marker = cnt;
          }
          break;
        case USB_POWER_CDP:
#ifndef EON
          // been CLICKS clicks since we switched to CDP
          if ((cnt-marker) >= CLICKS) {
            // measure current draw, if positive and no enumeration, switch to DCP
            if (!is_enumerated && current < CURRENT_THRESHOLD) {
              puts("USBP: no enumeration with current draw, switching to DCP mode\n");
              set_usb_power_mode(USB_POWER_DCP);
              marker = cnt;
            }
          }
          // keep resetting the timer if there's no current draw in CDP
          if (current >= CURRENT_THRESHOLD) {
            marker = cnt;
          }
#endif
          break;
        case USB_POWER_DCP:
          // been at least CLICKS clicks since we switched to DCP
          if ((cnt-marker) >= CLICKS) {
            // if no current draw, switch back to CDP
            if (current >= CURRENT_THRESHOLD) {
              puts("USBP: no current draw, switching back to CDP mode\n");
              set_usb_power_mode(USB_POWER_CDP);
              marker = cnt;
            }
          }
          // keep resetting the timer if there's current draw in DCP
          if (current < CURRENT_THRESHOLD) {
            marker = cnt;
          }
          break;
      }

      // ~0x9a = 500 ma
      /*puth(current);
      puts("\n");*/
    #endif

    // reset this every 16th pass
    if ((cnt&0xF) == 0) pending_can_live = 0;

    #ifdef DEBUG
      puts("** blink ");
      puth(can_rx_q.r_ptr); puts(" "); puth(can_rx_q.w_ptr); puts("  ");
      puth(can_tx1_q.r_ptr); puts(" "); puth(can_tx1_q.w_ptr); puts("  ");
      puth(can_tx2_q.r_ptr); puts(" "); puth(can_tx2_q.w_ptr); puts("\n");
    #endif

    // set green LED to be controls allowed
    set_led(LED_GREEN, controls_allowed);

    // blink the red LED
    int div_mode = ((usb_power_mode == USB_POWER_DCP) ? 4 : 1);

    for (int div_mode_loop = 0; div_mode_loop < div_mode; div_mode_loop++) {
      for (int fade = 0; fade < 1024; fade += 8) {
        for (int i = 0; i < 128/div_mode; i++) {
          set_led(LED_RED, 0);
          if (fade < 512) { delay(512-fade); } else { delay(fade-512); }
          set_led(LED_RED, 1);
          if (fade < 512) { delay(fade); } else { delay(1024-fade); }
        }
      }
    }

    // turn off the blue LED, turned on by CAN
    #ifdef PANDA
      set_led(LED_BLUE, 0);
    #endif
  }

  return 0;
}