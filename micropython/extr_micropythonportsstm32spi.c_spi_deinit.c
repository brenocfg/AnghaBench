#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * spi; } ;
typedef  TYPE_1__ spi_t ;
typedef  int /*<<< orphan*/  SPI_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_SPI_DeInit (int /*<<< orphan*/ *) ; 

void spi_deinit(const spi_t *spi_obj) {
    SPI_HandleTypeDef *spi = spi_obj->spi;
    HAL_SPI_DeInit(spi);
    if (0) {
    #if defined(MICROPY_HW_SPI1_SCK)
    } else if (spi->Instance == SPI1) {
        __HAL_RCC_SPI1_FORCE_RESET();
        __HAL_RCC_SPI1_RELEASE_RESET();
        __HAL_RCC_SPI1_CLK_DISABLE();
    #endif
    #if defined(MICROPY_HW_SPI2_SCK)
    } else if (spi->Instance == SPI2) {
        __HAL_RCC_SPI2_FORCE_RESET();
        __HAL_RCC_SPI2_RELEASE_RESET();
        __HAL_RCC_SPI2_CLK_DISABLE();
    #endif
    #if defined(MICROPY_HW_SPI3_SCK)
    } else if (spi->Instance == SPI3) {
        __HAL_RCC_SPI3_FORCE_RESET();
        __HAL_RCC_SPI3_RELEASE_RESET();
        __HAL_RCC_SPI3_CLK_DISABLE();
    #endif
    #if defined(MICROPY_HW_SPI4_SCK)
    } else if (spi->Instance == SPI4) {
        __HAL_RCC_SPI4_FORCE_RESET();
        __HAL_RCC_SPI4_RELEASE_RESET();
        __HAL_RCC_SPI4_CLK_DISABLE();
    #endif
    #if defined(MICROPY_HW_SPI5_SCK)
    } else if (spi->Instance == SPI5) {
        __HAL_RCC_SPI5_FORCE_RESET();
        __HAL_RCC_SPI5_RELEASE_RESET();
        __HAL_RCC_SPI5_CLK_DISABLE();
    #endif
    #if defined(MICROPY_HW_SPI6_SCK)
    } else if (spi->Instance == SPI6) {
        __HAL_RCC_SPI6_FORCE_RESET();
        __HAL_RCC_SPI6_RELEASE_RESET();
        __HAL_RCC_SPI6_CLK_DISABLE();
    #endif
    }
}