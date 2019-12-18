#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int is_enabled; int uart_id; TYPE_1__* uartx; } ;
typedef  TYPE_2__ pyb_uart_obj_t ;
struct TYPE_4__ {int /*<<< orphan*/  CR1; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_NVIC_DisableIRQ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UART10_IRQn ; 
 int /*<<< orphan*/  UART4_IRQn ; 
 int /*<<< orphan*/  UART5_IRQn ; 
 int /*<<< orphan*/  UART7_IRQn ; 
 int /*<<< orphan*/  UART8_IRQn ; 
 int /*<<< orphan*/  UART9_IRQn ; 
 int /*<<< orphan*/  USART1_IRQn ; 
 int /*<<< orphan*/  USART2_IRQn ; 
 int /*<<< orphan*/  USART3_IRQn ; 
 int /*<<< orphan*/  USART6_IRQn ; 
 int /*<<< orphan*/  USART_CR1_UE ; 
 int /*<<< orphan*/  __HAL_RCC_UART10_CLK_DISABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_UART10_FORCE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_UART10_RELEASE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_UART4_CLK_DISABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_UART4_FORCE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_UART4_RELEASE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_UART5_CLK_DISABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_UART5_FORCE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_UART5_RELEASE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_UART7_CLK_DISABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_UART7_FORCE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_UART7_RELEASE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_UART8_CLK_DISABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_UART8_FORCE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_UART8_RELEASE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_UART9_CLK_DISABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_UART9_FORCE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_UART9_RELEASE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_USART1_CLK_DISABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_USART1_FORCE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_USART1_RELEASE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_USART2_CLK_DISABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_USART2_FORCE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_USART2_RELEASE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_USART3_CLK_DISABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_USART3_FORCE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_USART3_RELEASE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_USART4_CLK_DISABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_USART4_FORCE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_USART4_RELEASE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_USART5_CLK_DISABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_USART5_FORCE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_USART5_RELEASE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_USART6_CLK_DISABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_USART6_FORCE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_USART6_RELEASE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_USART7_CLK_DISABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_USART7_FORCE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_USART7_RELEASE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_USART8_CLK_DISABLE () ; 
 int /*<<< orphan*/  __HAL_RCC_USART8_FORCE_RESET () ; 
 int /*<<< orphan*/  __HAL_RCC_USART8_RELEASE_RESET () ; 

void uart_deinit(pyb_uart_obj_t *self) {
    self->is_enabled = false;

    // Disable UART
    self->uartx->CR1 &= ~USART_CR1_UE;

    // Reset and turn off the UART peripheral
    if (self->uart_id == 1) {
        HAL_NVIC_DisableIRQ(USART1_IRQn);
        __HAL_RCC_USART1_FORCE_RESET();
        __HAL_RCC_USART1_RELEASE_RESET();
        __HAL_RCC_USART1_CLK_DISABLE();
    #if defined(USART2)
    } else if (self->uart_id == 2) {
        HAL_NVIC_DisableIRQ(USART2_IRQn);
        __HAL_RCC_USART2_FORCE_RESET();
        __HAL_RCC_USART2_RELEASE_RESET();
        __HAL_RCC_USART2_CLK_DISABLE();
    #endif
    #if defined(USART3)
    } else if (self->uart_id == 3) {
        #if !defined(STM32F0)
        HAL_NVIC_DisableIRQ(USART3_IRQn);
        #endif
        __HAL_RCC_USART3_FORCE_RESET();
        __HAL_RCC_USART3_RELEASE_RESET();
        __HAL_RCC_USART3_CLK_DISABLE();
    #endif
    #if defined(UART4)
    } else if (self->uart_id == 4) {
        HAL_NVIC_DisableIRQ(UART4_IRQn);
        __HAL_RCC_UART4_FORCE_RESET();
        __HAL_RCC_UART4_RELEASE_RESET();
        __HAL_RCC_UART4_CLK_DISABLE();
    #endif
    #if defined(USART4)
    } else if (self->uart_id == 4) {
        __HAL_RCC_USART4_FORCE_RESET();
        __HAL_RCC_USART4_RELEASE_RESET();
        __HAL_RCC_USART4_CLK_DISABLE();
    #endif
    #if defined(UART5)
    } else if (self->uart_id == 5) {
        HAL_NVIC_DisableIRQ(UART5_IRQn);
        __HAL_RCC_UART5_FORCE_RESET();
        __HAL_RCC_UART5_RELEASE_RESET();
        __HAL_RCC_UART5_CLK_DISABLE();
    #endif
    #if defined(USART5)
    } else if (self->uart_id == 5) {
        __HAL_RCC_USART5_FORCE_RESET();
        __HAL_RCC_USART5_RELEASE_RESET();
        __HAL_RCC_USART5_CLK_DISABLE();
    #endif
    #if defined(UART6)
    } else if (self->uart_id == 6) {
        HAL_NVIC_DisableIRQ(USART6_IRQn);
        __HAL_RCC_USART6_FORCE_RESET();
        __HAL_RCC_USART6_RELEASE_RESET();
        __HAL_RCC_USART6_CLK_DISABLE();
    #endif
    #if defined(UART7)
    } else if (self->uart_id == 7) {
        HAL_NVIC_DisableIRQ(UART7_IRQn);
        __HAL_RCC_UART7_FORCE_RESET();
        __HAL_RCC_UART7_RELEASE_RESET();
        __HAL_RCC_UART7_CLK_DISABLE();
    #endif
    #if defined(USART7)
    } else if (self->uart_id == 7) {
        __HAL_RCC_USART7_FORCE_RESET();
        __HAL_RCC_USART7_RELEASE_RESET();
        __HAL_RCC_USART7_CLK_DISABLE();
    #endif
    #if defined(UART8)
    } else if (self->uart_id == 8) {
        HAL_NVIC_DisableIRQ(UART8_IRQn);
        __HAL_RCC_UART8_FORCE_RESET();
        __HAL_RCC_UART8_RELEASE_RESET();
        __HAL_RCC_UART8_CLK_DISABLE();
    #endif
    #if defined(USART8)
    } else if (self->uart_id == 8) {
        __HAL_RCC_USART8_FORCE_RESET();
        __HAL_RCC_USART8_RELEASE_RESET();
        __HAL_RCC_USART8_CLK_DISABLE();
    #endif
    #if defined(UART9)
    } else if (self->uart_id == 9) {
        HAL_NVIC_DisableIRQ(UART9_IRQn);
        __HAL_RCC_UART9_FORCE_RESET();
        __HAL_RCC_UART9_RELEASE_RESET();
        __HAL_RCC_UART9_CLK_DISABLE();
    #endif
    #if defined(UART10)
    } else if (self->uart_id == 10) {
        HAL_NVIC_DisableIRQ(UART10_IRQn);
        __HAL_RCC_UART10_FORCE_RESET();
        __HAL_RCC_UART10_RELEASE_RESET();
        __HAL_RCC_UART10_CLK_DISABLE();
    #endif
    }
}