#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ APPLICATION_ADDR ; 
 int APP_VALIDITY_BITS ; 
 int /*<<< orphan*/  HSI_VALUE ; 
 int /*<<< orphan*/  LED0 ; 
 int /*<<< orphan*/  NVIC_PRIORITYGROUP_4 ; 
 int /*<<< orphan*/  NVIC_SetPriorityGrouping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemClock_Config () ; 
 int /*<<< orphan*/  SystemCoreClock ; 
 int /*<<< orphan*/  __set_MSP (int) ; 
 int /*<<< orphan*/  dfu_init () ; 
 int get_reset_mode () ; 
 int /*<<< orphan*/  led_init () ; 
 int /*<<< orphan*/  led_state (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  led_state_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_hal_delay_ms (int) ; 
 int /*<<< orphan*/  pyb_usbdd ; 
 int /*<<< orphan*/  pyb_usbdd_detect_port () ; 
 int /*<<< orphan*/  pyb_usbdd_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pyb_usbdd_start (int /*<<< orphan*/ *) ; 
 void stub1 (int) ; 

void stm32_main(int initial_r0) {
    #if defined(STM32F4)
    #if INSTRUCTION_CACHE_ENABLE
    __HAL_FLASH_INSTRUCTION_CACHE_ENABLE();
    #endif
    #if DATA_CACHE_ENABLE
    __HAL_FLASH_DATA_CACHE_ENABLE();
    #endif
    #if PREFETCH_ENABLE
    __HAL_FLASH_PREFETCH_BUFFER_ENABLE();
    #endif
    #elif defined(STM32F7)
    #if ART_ACCLERATOR_ENABLE
    __HAL_FLASH_ART_ENABLE();
    #endif
    #endif

    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    #if USE_CACHE && defined(STM32F7)
    SCB_EnableICache();
    SCB_EnableDCache();
    #endif

    #if defined(MBOOT_BOARD_EARLY_INIT)
    MBOOT_BOARD_EARLY_INIT();
    #endif

    #ifdef MBOOT_BOOTPIN_PIN
    mp_hal_pin_config(MBOOT_BOOTPIN_PIN, MP_HAL_PIN_MODE_INPUT, MBOOT_BOOTPIN_PULL, 0);
    if (mp_hal_pin_read(MBOOT_BOOTPIN_PIN) == MBOOT_BOOTPIN_ACTIVE) {
        goto enter_bootloader;
    }
    #endif

    if ((initial_r0 & 0xffffff00) == 0x70ad0000) {
        goto enter_bootloader;
    }

    // MCU starts up with HSI
    SystemCoreClock = HSI_VALUE;

    int reset_mode = get_reset_mode();
    uint32_t msp = *(volatile uint32_t*)APPLICATION_ADDR;
    if (reset_mode != 4 && (msp & APP_VALIDITY_BITS) == 0) {
        // not DFU mode so jump to application, passing through reset_mode
        // undo our DFU settings
        // TODO probably should disable all IRQ sources first
        #if USE_CACHE && defined(STM32F7)
        SCB_DisableICache();
        SCB_DisableDCache();
        #endif
        __set_MSP(msp);
        ((void (*)(uint32_t)) *((volatile uint32_t*)(APPLICATION_ADDR + 4)))(reset_mode);
    }

enter_bootloader:

    // Init subsystems (get_reset_mode() may call these, calling them again is ok)
    led_init();

    // set the system clock to be HSE
    SystemClock_Config();

    #if USE_USB_POLLING
    // irqs with a priority value greater or equal to "pri" will be disabled
    // "pri" should be between 1 and 15 inclusive
    uint32_t pri = 2;
    pri <<= (8 - __NVIC_PRIO_BITS);
    __ASM volatile ("msr basepri_max, %0" : : "r" (pri) : "memory");
    #endif

    #if defined(MBOOT_SPIFLASH_ADDR)
    MBOOT_SPIFLASH_SPIFLASH->config = MBOOT_SPIFLASH_CONFIG;
    mp_spiflash_init(MBOOT_SPIFLASH_SPIFLASH);
    #endif

    #if defined(MBOOT_SPIFLASH2_ADDR)
    MBOOT_SPIFLASH2_SPIFLASH->config = MBOOT_SPIFLASH2_CONFIG;
    mp_spiflash_init(MBOOT_SPIFLASH2_SPIFLASH);
    #endif

    #if MBOOT_FSLOAD
    if ((initial_r0 & 0xffffff80) == 0x70ad0080) {
        // Application passed through elements, validate then process them
        const uint8_t *elem_end = elem_search(ELEM_DATA_START, ELEM_TYPE_END);
        if (elem_end != NULL && elem_end[-1] == 0) {
            fsload_process();
        }
        // Always reset because the application is expecting to resume
        led_state_all(0);
        NVIC_SystemReset();
    }
    #endif

    dfu_init();

    pyb_usbdd_init(&pyb_usbdd, pyb_usbdd_detect_port());
    pyb_usbdd_start(&pyb_usbdd);

    #if defined(MBOOT_I2C_SCL)
    initial_r0 &= 0x7f;
    if (initial_r0 == 0) {
        initial_r0 = 0x23; // Default I2C address
    }
    i2c_init(initial_r0);
    #endif

    led_state_all(0);

    #if USE_USB_POLLING
    uint32_t ss = systick_ms;
    int ss2 = -1;
    #endif
    for (;;) {
        #if USE_USB_POLLING
        #if MBOOT_USB_AUTODETECT_PORT || MICROPY_HW_USB_MAIN_DEV == USB_PHY_FS_ID
        if (USB_OTG_FS->GINTSTS & USB_OTG_FS->GINTMSK) {
            HAL_PCD_IRQHandler(&pcd_fs_handle);
        }
        #endif
        #if MBOOT_USB_AUTODETECT_PORT || MICROPY_HW_USB_MAIN_DEV == USB_PHY_HS_ID
        if (USB_OTG_HS->GINTSTS & USB_OTG_HS->GINTMSK) {
            HAL_PCD_IRQHandler(&pcd_hs_handle);
        }
        #endif
        if (!pyb_usbdd.tx_pending) {
            dfu_process();
        }
        #endif

        #if USE_USB_POLLING
        //__WFI(); // slows it down way too much; might work with 10x faster systick
        if (systick_ms - ss > 50) {
            ss += 50;
            ss2 = (ss2 + 1) % 20;
            switch (ss2) {
                case 0: led_state(LED0, 1); break;
                case 1: led_state(LED0, 0); break;
            }
        }
        #else
        led_state(LED0, 1);
        mp_hal_delay_ms(50);
        led_state(LED0, 0);
        mp_hal_delay_ms(950);
        #endif
    }
}