#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {TYPE_3__* spi; } ;
typedef  TYPE_1__ spi_t ;
typedef  int mp_uint_t ;
typedef  int int32_t ;
struct TYPE_6__ {int FirstBit; int /*<<< orphan*/  DataSize; int /*<<< orphan*/  CLKPhase; int /*<<< orphan*/  CLKPolarity; int /*<<< orphan*/  BaudRatePrescaler; } ;
struct TYPE_7__ {scalar_t__ Instance; TYPE_2__ Init; } ;
typedef  TYPE_2__ SPI_InitTypeDef ;
typedef  TYPE_3__ SPI_HandleTypeDef ;

/* Variables and functions */
 int HAL_RCC_GetPCLK1Freq () ; 
 int HAL_RCC_GetPCLK2Freq () ; 
 scalar_t__ SPI3 ; 
 int /*<<< orphan*/  SPI_BAUDRATEPRESCALER_128 ; 
 int /*<<< orphan*/  SPI_BAUDRATEPRESCALER_16 ; 
 int /*<<< orphan*/  SPI_BAUDRATEPRESCALER_2 ; 
 int /*<<< orphan*/  SPI_BAUDRATEPRESCALER_256 ; 
 int /*<<< orphan*/  SPI_BAUDRATEPRESCALER_32 ; 
 int /*<<< orphan*/  SPI_BAUDRATEPRESCALER_4 ; 
 int /*<<< orphan*/  SPI_BAUDRATEPRESCALER_64 ; 
 int /*<<< orphan*/  SPI_BAUDRATEPRESCALER_8 ; 
 int /*<<< orphan*/  SPI_DATASIZE_16BIT ; 
 int /*<<< orphan*/  SPI_DATASIZE_8BIT ; 
 int /*<<< orphan*/  SPI_PHASE_1EDGE ; 
 int /*<<< orphan*/  SPI_PHASE_2EDGE ; 
 int /*<<< orphan*/  SPI_POLARITY_HIGH ; 
 int /*<<< orphan*/  SPI_POLARITY_LOW ; 

void spi_set_params(const spi_t *spi_obj, uint32_t prescale, int32_t baudrate,
    int32_t polarity, int32_t phase, int32_t bits, int32_t firstbit) {
    SPI_HandleTypeDef *spi = spi_obj->spi;
    SPI_InitTypeDef *init = &spi->Init;

    if (prescale != 0xffffffff || baudrate != -1) {
        if (prescale == 0xffffffff) {
            // prescaler not given, so select one that yields at most the requested baudrate
            mp_uint_t spi_clock;
            #if defined(STM32F0)
            spi_clock = HAL_RCC_GetPCLK1Freq();
            #elif defined(STM32H7)
            if (spi->Instance == SPI1 || spi->Instance == SPI2 || spi->Instance == SPI3) {
                spi_clock = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI123);
            } else if (spi->Instance == SPI4 || spi->Instance == SPI5) {
                spi_clock = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI45);
            } else {
                spi_clock = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_SPI6);
            }
            #else
            if (spi->Instance == SPI3) {
                // SPI3 is on APB1
                spi_clock = HAL_RCC_GetPCLK1Freq();
            #if defined(SPI2)
            } else if (spi->Instance == SPI2) {
                // SPI2 is on APB1
                spi_clock = HAL_RCC_GetPCLK1Freq();
            #endif
            } else {
                // SPI1, SPI4, SPI5 and SPI6 are on APB2
                spi_clock = HAL_RCC_GetPCLK2Freq();
            }
            #endif
            prescale = (spi_clock + baudrate - 1) / baudrate;
        }
        if (prescale <= 2) { init->BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2; }
        else if (prescale <= 4) { init->BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4; }
        else if (prescale <= 8) { init->BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8; }
        else if (prescale <= 16) { init->BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16; }
        else if (prescale <= 32) { init->BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32; }
        else if (prescale <= 64) { init->BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64; }
        else if (prescale <= 128) { init->BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128; }
        else { init->BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256; }
    }

    if (polarity != -1) {
        init->CLKPolarity = polarity == 0 ? SPI_POLARITY_LOW : SPI_POLARITY_HIGH;
    }

    if (phase != -1) {
        init->CLKPhase = phase == 0 ? SPI_PHASE_1EDGE : SPI_PHASE_2EDGE;
    }

    if (bits != -1) {
        init->DataSize = (bits == 16) ? SPI_DATASIZE_16BIT : SPI_DATASIZE_8BIT;
    }

    if (firstbit != -1) {
        init->FirstBit = firstbit;
    }
}