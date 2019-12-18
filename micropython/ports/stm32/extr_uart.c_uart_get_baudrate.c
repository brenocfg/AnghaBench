#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int uart_id; TYPE_1__* uartx; } ;
typedef  TYPE_2__ pyb_uart_obj_t ;
struct TYPE_7__ {int DCKCFGR2; int D2CCIP2R; } ;
struct TYPE_5__ {int BRR; } ;

/* Variables and functions */
 int CSI_VALUE ; 
 int HAL_RCC_GetPCLK1Freq () ; 
 int HAL_RCC_GetPCLK2Freq () ; 
 int HAL_RCC_GetSysClockFreq () ; 
 int HSI_VALUE ; 
 int LSE_VALUE ; 
 TYPE_4__* RCC ; 

uint32_t uart_get_baudrate(pyb_uart_obj_t *self) {
    uint32_t uart_clk = 0;

    #if defined(STM32F0)
    uart_clk = HAL_RCC_GetPCLK1Freq();
    #elif defined(STM32F7)
    switch ((RCC->DCKCFGR2 >> ((self->uart_id - 1) * 2)) & 3) {
        case 0:
            if (self->uart_id == 1 || self->uart_id == 6) {
                uart_clk = HAL_RCC_GetPCLK2Freq();
            } else {
                uart_clk = HAL_RCC_GetPCLK1Freq();
            }
            break;
        case 1:
            uart_clk = HAL_RCC_GetSysClockFreq();
            break;
        case 2:
            uart_clk = HSI_VALUE;
            break;
        case 3:
            uart_clk = LSE_VALUE;
            break;
    }
    #elif defined(STM32H7)
    uint32_t csel;
    if (self->uart_id == 1 || self->uart_id == 6) {
        csel = RCC->D2CCIP2R >> 3;
    } else {
        csel = RCC->D2CCIP2R;
    }
    switch (csel & 3) {
        case 0:
            if (self->uart_id == 1 || self->uart_id == 6) {
                uart_clk = HAL_RCC_GetPCLK2Freq();
            } else {
                uart_clk = HAL_RCC_GetPCLK1Freq();
            }
            break;
        case 3:
            uart_clk = HSI_VALUE;
            break;
        case 4:
            uart_clk = CSI_VALUE;
            break;
        case 5:
            uart_clk = LSE_VALUE;
            break;
        default:
            break;
    }
    #else
    if (self->uart_id == 1
        #if defined(USART6)
        || self->uart_id == 6
        #endif
        #if defined(UART9)
        || self->uart_id == 9
        #endif
        #if defined(UART10)
        || self->uart_id == 10
        #endif
        ) {
        uart_clk = HAL_RCC_GetPCLK2Freq();
    } else {
        uart_clk = HAL_RCC_GetPCLK1Freq();
    }
    #endif

    // This formula assumes UART_OVERSAMPLING_16
    uint32_t baudrate = uart_clk / self->uartx->BRR;

    return baudrate;
}