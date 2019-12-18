#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int uint ;
struct TYPE_23__ {int uart_id; int is_enabled; int attached_to_repl; int char_mask; int /*<<< orphan*/ * mp_irq_obj; scalar_t__ mp_irq_trigger; int /*<<< orphan*/  char_width; TYPE_3__* uartx; } ;
typedef  TYPE_2__ pyb_uart_obj_t ;
typedef  int /*<<< orphan*/  pin_obj_t ;
typedef  int /*<<< orphan*/  huart ;
struct TYPE_24__ {int /*<<< orphan*/  CR3; int /*<<< orphan*/  CR2; int /*<<< orphan*/  CR1; } ;
typedef  TYPE_3__ USART_TypeDef ;
struct TYPE_22__ {int /*<<< orphan*/  OverSampling; scalar_t__ HwFlowCtl; int /*<<< orphan*/  Mode; scalar_t__ Parity; scalar_t__ StopBits; scalar_t__ WordLength; scalar_t__ BaudRate; } ;
struct TYPE_25__ {TYPE_1__ Init; TYPE_3__* Instance; } ;
typedef  TYPE_4__ UART_HandleTypeDef ;
typedef  int /*<<< orphan*/  IRQn_Type ;

/* Variables and functions */
 int /*<<< orphan*/  AF_FN_UART ; 
 int /*<<< orphan*/  CHAR_WIDTH_8BIT ; 
 int /*<<< orphan*/  CHAR_WIDTH_9BIT ; 
 int /*<<< orphan*/  HAL_NVIC_EnableIRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAL_UART_Init (TYPE_4__*) ; 
 int /*<<< orphan*/  IRQ_PRI_UART ; 
 int /*<<< orphan*/  IRQn_NONNEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MICROPY_HW_UART10_RX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART10_TX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART1_RX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART1_TX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART2_CTS ; 
 int /*<<< orphan*/ * MICROPY_HW_UART2_RTS ; 
 int /*<<< orphan*/ * MICROPY_HW_UART2_RX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART2_TX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART3_CTS ; 
 int /*<<< orphan*/ * MICROPY_HW_UART3_RTS ; 
 int /*<<< orphan*/ * MICROPY_HW_UART3_RX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART3_TX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART4_CTS ; 
 int /*<<< orphan*/ * MICROPY_HW_UART4_RTS ; 
 int /*<<< orphan*/ * MICROPY_HW_UART4_RX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART4_TX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART5_RX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART5_TX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART6_CTS ; 
 int /*<<< orphan*/ * MICROPY_HW_UART6_RTS ; 
 int /*<<< orphan*/ * MICROPY_HW_UART6_RX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART6_TX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART7_RX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART7_TX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART8_RX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART8_TX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART9_RX ; 
 int /*<<< orphan*/ * MICROPY_HW_UART9_TX ; 
 scalar_t__ MP_HAL_PIN_MODE_ALT ; 
 scalar_t__ MP_HAL_PIN_PULL_UP ; 
 int /*<<< orphan*/  NVIC_SetPriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  PYB_UART_1 137 
#define  PYB_UART_10 136 
#define  PYB_UART_2 135 
#define  PYB_UART_3 134 
#define  PYB_UART_4 133 
#define  PYB_UART_5 132 
#define  PYB_UART_6 131 
#define  PYB_UART_7 130 
#define  PYB_UART_8 129 
#define  PYB_UART_9 128 
 TYPE_3__* UART10 ; 
 int /*<<< orphan*/  UART10_IRQn ; 
 TYPE_3__* UART4 ; 
 int /*<<< orphan*/  UART4_IRQn ; 
 TYPE_3__* UART5 ; 
 int /*<<< orphan*/  UART5_IRQn ; 
 TYPE_3__* UART7 ; 
 int /*<<< orphan*/  UART7_IRQn ; 
 TYPE_3__* UART8 ; 
 int /*<<< orphan*/  UART8_IRQn ; 
 TYPE_3__* UART9 ; 
 int /*<<< orphan*/  UART9_IRQn ; 
 scalar_t__ UART_HWCONTROL_CTS ; 
 scalar_t__ UART_HWCONTROL_RTS ; 
 int /*<<< orphan*/  UART_MODE_TX_RX ; 
 int /*<<< orphan*/  UART_OVERSAMPLING_16 ; 
 scalar_t__ UART_PARITY_NONE ; 
 scalar_t__ UART_WORDLENGTH_9B ; 
 TYPE_3__* USART1 ; 
 int /*<<< orphan*/  USART1_IRQn ; 
 TYPE_3__* USART2 ; 
 int /*<<< orphan*/  USART2_IRQn ; 
 TYPE_3__* USART3 ; 
 int /*<<< orphan*/  USART3_8_IRQn ; 
 int /*<<< orphan*/  USART3_IRQn ; 
 TYPE_3__* USART4 ; 
 TYPE_3__* USART5 ; 
 TYPE_3__* USART6 ; 
 int /*<<< orphan*/  USART6_IRQn ; 
 TYPE_3__* USART7 ; 
 TYPE_3__* USART8 ; 
 int /*<<< orphan*/  USART_CR1_IE_ALL ; 
 int /*<<< orphan*/  USART_CR2_IE_ALL ; 
 int /*<<< orphan*/  USART_CR3_IE_ALL ; 
 int /*<<< orphan*/  __HAL_RCC_UART10_CLK_ENABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_UART4_CLK_ENABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_UART5_CLK_ENABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_UART7_CLK_ENABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_UART8_CLK_ENABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_UART9_CLK_ENABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_USART1_CLK_ENABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_USART2_CLK_ENABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_USART3_CLK_ENABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_USART4_CLK_ENABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_USART5_CLK_ENABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_USART6_CLK_ENABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_USART7_CLK_ENABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_USART8_CLK_ENABLE () ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int mp_hal_pin_config_alt (int /*<<< orphan*/  const*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 

bool uart_init(pyb_uart_obj_t *uart_obj,
    uint32_t baudrate, uint32_t bits, uint32_t parity, uint32_t stop, uint32_t flow) {
    USART_TypeDef *UARTx;
    IRQn_Type irqn;
    int uart_unit;

    const pin_obj_t *pins[4] = {0};

    switch (uart_obj->uart_id) {
        #if defined(MICROPY_HW_UART1_TX) && defined(MICROPY_HW_UART1_RX)
        case PYB_UART_1:
            uart_unit = 1;
            UARTx = USART1;
            irqn = USART1_IRQn;
            pins[0] = MICROPY_HW_UART1_TX;
            pins[1] = MICROPY_HW_UART1_RX;
            __HAL_RCC_USART1_CLK_ENABLE();
            break;
        #endif

        #if defined(MICROPY_HW_UART2_TX) && defined(MICROPY_HW_UART2_RX)
        case PYB_UART_2:
            uart_unit = 2;
            UARTx = USART2;
            irqn = USART2_IRQn;
            pins[0] = MICROPY_HW_UART2_TX;
            pins[1] = MICROPY_HW_UART2_RX;
            #if defined(MICROPY_HW_UART2_RTS)
            if (flow & UART_HWCONTROL_RTS) {
                pins[2] = MICROPY_HW_UART2_RTS;
            }
            #endif
            #if defined(MICROPY_HW_UART2_CTS)
            if (flow & UART_HWCONTROL_CTS) {
                pins[3] = MICROPY_HW_UART2_CTS;
            }
            #endif
            __HAL_RCC_USART2_CLK_ENABLE();
            break;
        #endif

        #if defined(MICROPY_HW_UART3_TX) && defined(MICROPY_HW_UART3_RX)
        case PYB_UART_3:
            uart_unit = 3;
            UARTx = USART3;
            #if defined(STM32F0)
            irqn = USART3_8_IRQn;
            #else
            irqn = USART3_IRQn;
            #endif
            pins[0] = MICROPY_HW_UART3_TX;
            pins[1] = MICROPY_HW_UART3_RX;
            #if defined(MICROPY_HW_UART3_RTS)
            if (flow & UART_HWCONTROL_RTS) {
                pins[2] = MICROPY_HW_UART3_RTS;
            }
            #endif
            #if defined(MICROPY_HW_UART3_CTS)
            if (flow & UART_HWCONTROL_CTS) {
                pins[3] = MICROPY_HW_UART3_CTS;
            }
            #endif
            __HAL_RCC_USART3_CLK_ENABLE();
            break;
        #endif

        #if defined(MICROPY_HW_UART4_TX) && defined(MICROPY_HW_UART4_RX)
        case PYB_UART_4:
            uart_unit = 4;
            #if defined(STM32F0)
            UARTx = USART4;
            irqn = USART3_8_IRQn;
            __HAL_RCC_USART4_CLK_ENABLE();
            #else
            UARTx = UART4;
            irqn = UART4_IRQn;
            __HAL_RCC_UART4_CLK_ENABLE();
            #endif
            pins[0] = MICROPY_HW_UART4_TX;
            pins[1] = MICROPY_HW_UART4_RX;
            #if defined(MICROPY_HW_UART4_RTS)
            if (flow & UART_HWCONTROL_RTS) {
                pins[2] = MICROPY_HW_UART4_RTS;
            }
            #endif
            #if defined(MICROPY_HW_UART4_CTS)
            if (flow & UART_HWCONTROL_CTS) {
                pins[3] = MICROPY_HW_UART4_CTS;
            }
            #endif
            break;
        #endif

        #if defined(MICROPY_HW_UART5_TX) && defined(MICROPY_HW_UART5_RX)
        case PYB_UART_5:
            uart_unit = 5;
            #if defined(STM32F0)
            UARTx = USART5;
            irqn = USART3_8_IRQn;
            __HAL_RCC_USART5_CLK_ENABLE();
            #else
            UARTx = UART5;
            irqn = UART5_IRQn;
            __HAL_RCC_UART5_CLK_ENABLE();
            #endif
            pins[0] = MICROPY_HW_UART5_TX;
            pins[1] = MICROPY_HW_UART5_RX;
            break;
        #endif

        #if defined(MICROPY_HW_UART6_TX) && defined(MICROPY_HW_UART6_RX)
        case PYB_UART_6:
            uart_unit = 6;
            UARTx = USART6;
            #if defined(STM32F0)
            irqn = USART3_8_IRQn;
            #else
            irqn = USART6_IRQn;
            #endif
            pins[0] = MICROPY_HW_UART6_TX;
            pins[1] = MICROPY_HW_UART6_RX;
            #if defined(MICROPY_HW_UART6_RTS)
            if (flow & UART_HWCONTROL_RTS) {
                pins[2] = MICROPY_HW_UART6_RTS;
            }
            #endif
            #if defined(MICROPY_HW_UART6_CTS)
            if (flow & UART_HWCONTROL_CTS) {
                pins[3] = MICROPY_HW_UART6_CTS;
            }
            #endif
            __HAL_RCC_USART6_CLK_ENABLE();
            break;
        #endif

        #if defined(MICROPY_HW_UART7_TX) && defined(MICROPY_HW_UART7_RX)
        case PYB_UART_7:
            uart_unit = 7;
            #if defined(STM32F0)
            UARTx = USART7;
            irqn = USART3_8_IRQn;
            __HAL_RCC_USART7_CLK_ENABLE();
            #else
            UARTx = UART7;
            irqn = UART7_IRQn;
            __HAL_RCC_UART7_CLK_ENABLE();
            #endif
            pins[0] = MICROPY_HW_UART7_TX;
            pins[1] = MICROPY_HW_UART7_RX;
            break;
        #endif

        #if defined(MICROPY_HW_UART8_TX) && defined(MICROPY_HW_UART8_RX)
        case PYB_UART_8:
            uart_unit = 8;
            #if defined(STM32F0)
            UARTx = USART8;
            irqn = USART3_8_IRQn;
            __HAL_RCC_USART8_CLK_ENABLE();
            #else
            UARTx = UART8;
            irqn = UART8_IRQn;
            __HAL_RCC_UART8_CLK_ENABLE();
            #endif
            pins[0] = MICROPY_HW_UART8_TX;
            pins[1] = MICROPY_HW_UART8_RX;
            break;
        #endif

        #if defined(MICROPY_HW_UART9_TX) && defined(MICROPY_HW_UART9_RX)
        case PYB_UART_9:
            uart_unit = 9;
            UARTx = UART9;
            irqn = UART9_IRQn;
            __HAL_RCC_UART9_CLK_ENABLE();
            pins[0] = MICROPY_HW_UART9_TX;
            pins[1] = MICROPY_HW_UART9_RX;
            break;
        #endif

        #if defined(MICROPY_HW_UART10_TX) && defined(MICROPY_HW_UART10_RX)
        case PYB_UART_10:
            uart_unit = 10;
            UARTx = UART10;
            irqn = UART10_IRQn;
            __HAL_RCC_UART10_CLK_ENABLE();
            pins[0] = MICROPY_HW_UART10_TX;
            pins[1] = MICROPY_HW_UART10_RX;
            break;
        #endif

        default:
            // UART does not exist or is not configured for this board
            return false;
    }

    uint32_t mode = MP_HAL_PIN_MODE_ALT;
    uint32_t pull = MP_HAL_PIN_PULL_UP;

    for (uint i = 0; i < 4; i++) {
        if (pins[i] != NULL) {
            bool ret = mp_hal_pin_config_alt(pins[i], mode, pull, AF_FN_UART, uart_unit);
            if (!ret) {
                return false;
            }
        }
    }

    uart_obj->uartx = UARTx;

    // init UARTx
    UART_HandleTypeDef huart;
    memset(&huart, 0, sizeof(huart));
    huart.Instance = UARTx;
    huart.Init.BaudRate = baudrate;
    huart.Init.WordLength = bits;
    huart.Init.StopBits = stop;
    huart.Init.Parity = parity;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = flow;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart);

    // Disable all individual UART IRQs, but enable the global handler
    uart_obj->uartx->CR1 &= ~USART_CR1_IE_ALL;
    uart_obj->uartx->CR2 &= ~USART_CR2_IE_ALL;
    uart_obj->uartx->CR3 &= ~USART_CR3_IE_ALL;
    NVIC_SetPriority(IRQn_NONNEG(irqn), IRQ_PRI_UART);
    HAL_NVIC_EnableIRQ(irqn);

    uart_obj->is_enabled = true;
    uart_obj->attached_to_repl = false;

    if (bits == UART_WORDLENGTH_9B && parity == UART_PARITY_NONE) {
        uart_obj->char_mask = 0x1ff;
        uart_obj->char_width = CHAR_WIDTH_9BIT;
    } else {
        if (bits == UART_WORDLENGTH_9B || parity == UART_PARITY_NONE) {
            uart_obj->char_mask = 0xff;
        } else {
            uart_obj->char_mask = 0x7f;
        }
        uart_obj->char_width = CHAR_WIDTH_8BIT;
    }

    uart_obj->mp_irq_trigger = 0;
    uart_obj->mp_irq_obj = NULL;

    return true;
}