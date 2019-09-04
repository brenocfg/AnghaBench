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
typedef  int uint32_t ;
struct TYPE_8__ {int ClockType; } ;
struct TYPE_6__ {int PLLM; int PLLN; int PLLP; int /*<<< orphan*/  PLLQ; int /*<<< orphan*/  PLLState; } ;
struct TYPE_7__ {TYPE_1__ PLL; } ;
typedef  TYPE_2__ RCC_OscInitTypeDef ;
typedef  TYPE_3__ RCC_ClkInitTypeDef ;

/* Variables and functions */
 scalar_t__ HAL_OK ; 
 scalar_t__ HAL_RCC_OscConfig (TYPE_2__*) ; 
 int MICROPY_HW_CLK_PLLM ; 
 int MICROPY_HW_CLK_PLLN ; 
 int MICROPY_HW_CLK_PLLP ; 
 int /*<<< orphan*/  MICROPY_HW_CLK_PLLQ ; 
 int MICROPY_HW_CLK_VALUE ; 
 int RCC_CLOCKTYPE_HCLK ; 
 int RCC_CLOCKTYPE_PCLK1 ; 
 int RCC_CLOCKTYPE_PCLK2 ; 
 int RCC_CLOCKTYPE_SYSCLK ; 
 int /*<<< orphan*/  RCC_PLL_ON ; 
 int /*<<< orphan*/  __fatal_error (char*) ; 
 scalar_t__ powerctrl_rcc_clock_config_pll (TYPE_3__*,int,int) ; 

void SystemClock_Config(void)
{
    #if defined(STM32F7)
    // The DFU bootloader changes the clocksource register from its default power
    // on reset value, so we set it back here, so the clocksources are the same
    // whether we were started from DFU or from a power on reset.
    RCC->DCKCFGR2 = 0;
    #endif

    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;
    #if defined(STM32H7)
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
    #endif

    #if defined(STM32F4) || defined(STM32F7) || defined(STM32H7)

    /* Enable Power Control clock */
    #if defined(STM32H7)
    MODIFY_REG(PWR->CR3, PWR_CR3_SCUEN, 0);
    #else
    __PWR_CLK_ENABLE();
    #endif

    /* The voltage scaling allows optimizing the power consumption when the device is
       clocked below the maximum system frequency, to update the voltage scaling value
       regarding system frequency refer to product datasheet.  */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
    #elif defined(STM32L4)
    // Configure LSE Drive Capability
    __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
    #endif

    #if defined(STM32H7)
    // Wait for PWR_FLAG_VOSRDY
    while ((PWR->D3CR & (PWR_D3CR_VOSRDY)) != PWR_D3CR_VOSRDY) {
    }
    #endif

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    #if defined(STM32F4) || defined(STM32F7) || defined(STM32H7)
    RCC_OscInitStruct.OscillatorType = MICROPY_HW_RCC_OSCILLATOR_TYPE;
    RCC_OscInitStruct.HSEState = MICROPY_HW_RCC_HSE_STATE;
    RCC_OscInitStruct.HSIState = MICROPY_HW_RCC_HSI_STATE;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    #if defined(STM32H7)
    RCC_OscInitStruct.CSIState = RCC_CSI_OFF;
    #endif
    RCC_OscInitStruct.PLL.PLLSource = MICROPY_HW_RCC_PLL_SRC;
    #elif defined(STM32L4)
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
    #endif
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    #if defined(STM32H7)
    RCC_ClkInitStruct.ClockType |= (RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1);
    #endif

#if defined(MICROPY_HW_CLK_LAST_FREQ) && MICROPY_HW_CLK_LAST_FREQ
    #if defined(STM32F7)
    #define FREQ_BKP BKP31R
    #elif defined(STM32L4)
    #error Unsupported Processor
    #else
    #define FREQ_BKP BKP19R
    #endif
    uint32_t m = RTC->FREQ_BKP;
    uint32_t n;
    uint32_t p;
    uint32_t q;

    // 222111HH HHQQQQPP nNNNNNNN NNMMMMMM
    uint32_t h = (m >> 22) & 0xf;
    uint32_t b1 = (m >> 26) & 0x7;
    uint32_t b2 = (m >> 29) & 0x7;
    q = (m >> 18) & 0xf;
    p = (((m >> 16) & 0x03)+1)*2;
    n = (m >> 6) & 0x3ff;
    m &= 0x3f;
    if ((q < 2) || (q > 15) || (p > 8) || (p < 2) || (n < 192) || (n >= 433) || (m < 2)) {
        m = MICROPY_HW_CLK_PLLM;
        n = MICROPY_HW_CLK_PLLN;
        p = MICROPY_HW_CLK_PLLP;
        q = MICROPY_HW_CLK_PLLQ;
        h = RCC_SYSCLK_DIV1;
        b1 = RCC_HCLK_DIV4;
        b2 = RCC_HCLK_DIV2;
    } else {
        h <<= 4;
        b1 <<= 10;
        b2 <<= 10;
    }
    RCC_OscInitStruct.PLL.PLLM = m; //MICROPY_HW_CLK_PLLM;
    RCC_OscInitStruct.PLL.PLLN = n; //MICROPY_HW_CLK_PLLN;
    RCC_OscInitStruct.PLL.PLLP = p; //MICROPY_HW_CLK_PLLP;
    RCC_OscInitStruct.PLL.PLLQ = q; //MICROPY_HW_CLK_PLLQ;

    RCC_ClkInitStruct.AHBCLKDivider = h;  //RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = b1; //RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = b2; //RCC_HCLK_DIV2;
#else // defined(MICROPY_HW_CLK_LAST_FREQ) && MICROPY_HW_CLK_LAST_FREQ
    RCC_OscInitStruct.PLL.PLLM = MICROPY_HW_CLK_PLLM;
    RCC_OscInitStruct.PLL.PLLN = MICROPY_HW_CLK_PLLN;
    RCC_OscInitStruct.PLL.PLLP = MICROPY_HW_CLK_PLLP;
    RCC_OscInitStruct.PLL.PLLQ = MICROPY_HW_CLK_PLLQ;
    #if defined(STM32L4) || defined(STM32H7)
    RCC_OscInitStruct.PLL.PLLR = MICROPY_HW_CLK_PLLR;
    #endif

    #if defined(STM32H7)
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_1;
    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
    RCC_OscInitStruct.PLL.PLLFRACN = 0;
    #endif

    #if defined(STM32F4) || defined(STM32F7)
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    #elif defined(STM32L4)
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    #elif defined(STM32H7)
    RCC_ClkInitStruct.SYSCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;
    #endif
#endif

    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
      __fatal_error("HAL_RCC_OscConfig");
    }

#if defined(STM32H7)
    /* PLL3 for USB Clock */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLL3;
    PeriphClkInitStruct.PLL3.PLL3M = MICROPY_HW_CLK_PLL3M;
    PeriphClkInitStruct.PLL3.PLL3N = MICROPY_HW_CLK_PLL3N;
    PeriphClkInitStruct.PLL3.PLL3P = MICROPY_HW_CLK_PLL3P;
    PeriphClkInitStruct.PLL3.PLL3Q = MICROPY_HW_CLK_PLL3Q;
    PeriphClkInitStruct.PLL3.PLL3R = MICROPY_HW_CLK_PLL3R;
    PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_1;
    PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
    PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
        __fatal_error("HAL_RCCEx_PeriphCLKConfig");
    }
#endif

#if defined(STM32F7)
  /* Activate the OverDrive to reach the 200 MHz Frequency */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    __fatal_error("HAL_PWREx_EnableOverDrive");
  }
#endif

    uint32_t vco_out = RCC_OscInitStruct.PLL.PLLN * (MICROPY_HW_CLK_VALUE / 1000000) / RCC_OscInitStruct.PLL.PLLM;
    uint32_t sysclk_mhz = vco_out / RCC_OscInitStruct.PLL.PLLP;
    bool need_pllsai = vco_out % 48 != 0;
    if (powerctrl_rcc_clock_config_pll(&RCC_ClkInitStruct, sysclk_mhz, need_pllsai) != 0) {
        __fatal_error("HAL_RCC_ClockConfig");
    }

#if defined(STM32H7)
  /* Activate CSI clock mandatory for I/O Compensation Cell*/
  __HAL_RCC_CSI_ENABLE() ;

  /* Enable SYSCFG clock mandatory for I/O Compensation Cell */
  __HAL_RCC_SYSCFG_CLK_ENABLE() ;

  /* Enable the I/O Compensation Cell */
  HAL_EnableCompensationCell();

  /* Enable the USB voltage level detector */
  HAL_PWREx_EnableUSBVoltageDetector();
#endif

#if defined(STM32L4)
    // Enable MSI-Hardware auto calibration mode with LSE
    HAL_RCCEx_EnableMSIPLLMode();

    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SAI1|RCC_PERIPHCLK_I2C1
                                              |RCC_PERIPHCLK_USB |RCC_PERIPHCLK_ADC
                                              |RCC_PERIPHCLK_RNG |RCC_PERIPHCLK_RTC;
    PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
    /* PLLSAI is used to clock USB, ADC, I2C1 and RNG. The frequency is
       MSI(4MHz)/PLLM(1)*PLLSAI1N(24)/PLLSAIQ(2) = 48MHz. See the STM32CubeMx
       application or the reference manual. */
    PeriphClkInitStruct.Sai1ClockSelection = RCC_SAI1CLKSOURCE_PLLSAI1;
    PeriphClkInitStruct.AdcClockSelection = RCC_ADCCLKSOURCE_PLLSAI1;
    PeriphClkInitStruct.UsbClockSelection = RCC_USBCLKSOURCE_PLLSAI1;
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
    PeriphClkInitStruct.RngClockSelection = RCC_RNGCLKSOURCE_PLLSAI1;
    PeriphClkInitStruct.PLLSAI1.PLLSAI1Source = RCC_PLLSOURCE_MSI;
    PeriphClkInitStruct.PLLSAI1.PLLSAI1M = 1;
    PeriphClkInitStruct.PLLSAI1.PLLSAI1N = 24;
    PeriphClkInitStruct.PLLSAI1.PLLSAI1P = RCC_PLLP_DIV7;
    PeriphClkInitStruct.PLLSAI1.PLLSAI1Q = RCC_PLLQ_DIV2;
    PeriphClkInitStruct.PLLSAI1.PLLSAI1R = RCC_PLLR_DIV2;
    PeriphClkInitStruct.PLLSAI1.PLLSAI1ClockOut = RCC_PLLSAI1_SAI1CLK
                                                 |RCC_PLLSAI1_48M2CLK
                                                 |RCC_PLLSAI1_ADC1CLK;

    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
        __fatal_error("HAL_RCCEx_PeriphCLKConfig");
    }

    __PWR_CLK_ENABLE();

    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_PRIORITYGROUP_4, TICK_INT_PRIORITY, 0));
#endif
}