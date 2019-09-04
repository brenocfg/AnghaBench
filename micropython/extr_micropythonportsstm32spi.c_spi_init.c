#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint ;
struct TYPE_8__ {int /*<<< orphan*/  rx_dma_descr; int /*<<< orphan*/  tx_dma_descr; TYPE_3__* spi; } ;
typedef  TYPE_2__ spi_t ;
typedef  int /*<<< orphan*/  pin_obj_t ;
struct TYPE_7__ {scalar_t__ CLKPolarity; } ;
struct TYPE_9__ {TYPE_1__ Init; } ;
typedef  TYPE_3__ SPI_HandleTypeDef ;

/* Variables and functions */
 int /*<<< orphan*/  AF_FN_SPI ; 
 scalar_t__ HAL_OK ; 
 scalar_t__ HAL_SPI_Init (TYPE_3__*) ; 
 int /*<<< orphan*/  MP_HAL_PIN_MODE_ALT ; 
 int /*<<< orphan*/  MP_HAL_PIN_PULL_DOWN ; 
 int /*<<< orphan*/  MP_HAL_PIN_PULL_UP ; 
 scalar_t__ SPI_POLARITY_LOW ; 
 int /*<<< orphan*/  dma_invalidate_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_hal_pin_config_alt (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_2__ const* spi_obj ; 

void spi_init(const spi_t *self, bool enable_nss_pin) {
    SPI_HandleTypeDef *spi = self->spi;
    const pin_obj_t *pins[4] = { NULL, NULL, NULL, NULL };

    if (0) {
    #if defined(MICROPY_HW_SPI1_SCK)
    } else if (spi->Instance == SPI1) {
        #if defined(MICROPY_HW_SPI1_NSS)
        pins[0] = MICROPY_HW_SPI1_NSS;
        #endif
        pins[1] = MICROPY_HW_SPI1_SCK;
        #if defined(MICROPY_HW_SPI1_MISO)
        pins[2] = MICROPY_HW_SPI1_MISO;
        #endif
        pins[3] = MICROPY_HW_SPI1_MOSI;
        // enable the SPI clock
        __HAL_RCC_SPI1_CLK_ENABLE();
    #endif
    #if defined(MICROPY_HW_SPI2_SCK)
    } else if (spi->Instance == SPI2) {
        #if defined(MICROPY_HW_SPI2_NSS)
        pins[0] = MICROPY_HW_SPI2_NSS;
        #endif
        pins[1] = MICROPY_HW_SPI2_SCK;
        #if defined(MICROPY_HW_SPI2_MISO)
        pins[2] = MICROPY_HW_SPI2_MISO;
        #endif
        pins[3] = MICROPY_HW_SPI2_MOSI;
        // enable the SPI clock
        __HAL_RCC_SPI2_CLK_ENABLE();
    #endif
    #if defined(MICROPY_HW_SPI3_SCK)
    } else if (spi->Instance == SPI3) {
        #if defined(MICROPY_HW_SPI3_NSS)
        pins[0] = MICROPY_HW_SPI3_NSS;
        #endif
        pins[1] = MICROPY_HW_SPI3_SCK;
        #if defined(MICROPY_HW_SPI3_MISO)
        pins[2] = MICROPY_HW_SPI3_MISO;
        #endif
        pins[3] = MICROPY_HW_SPI3_MOSI;
        // enable the SPI clock
        __HAL_RCC_SPI3_CLK_ENABLE();
    #endif
    #if defined(MICROPY_HW_SPI4_SCK)
    } else if (spi->Instance == SPI4) {
        #if defined(MICROPY_HW_SPI4_NSS)
        pins[0] = MICROPY_HW_SPI4_NSS;
        #endif
        pins[1] = MICROPY_HW_SPI4_SCK;
        #if defined(MICROPY_HW_SPI4_MISO)
        pins[2] = MICROPY_HW_SPI4_MISO;
        #endif
        pins[3] = MICROPY_HW_SPI4_MOSI;
        // enable the SPI clock
        __HAL_RCC_SPI4_CLK_ENABLE();
    #endif
    #if defined(MICROPY_HW_SPI5_SCK)
    } else if (spi->Instance == SPI5) {
        #if defined(MICROPY_HW_SPI5_NSS)
        pins[0] = MICROPY_HW_SPI5_NSS;
        #endif
        pins[1] = MICROPY_HW_SPI5_SCK;
        #if defined(MICROPY_HW_SPI5_MISO)
        pins[2] = MICROPY_HW_SPI5_MISO;
        #endif
        pins[3] = MICROPY_HW_SPI5_MOSI;
        // enable the SPI clock
        __HAL_RCC_SPI5_CLK_ENABLE();
    #endif
    #if defined(MICROPY_HW_SPI6_SCK)
    } else if (spi->Instance == SPI6) {
        #if defined(MICROPY_HW_SPI6_NSS)
        pins[0] = MICROPY_HW_SPI6_NSS;
        #endif
        pins[1] = MICROPY_HW_SPI6_SCK;
        #if defined(MICROPY_HW_SPI6_MISO)
        pins[2] = MICROPY_HW_SPI6_MISO;
        #endif
        pins[3] = MICROPY_HW_SPI6_MOSI;
        // enable the SPI clock
        __HAL_RCC_SPI6_CLK_ENABLE();
    #endif
    } else {
        // SPI does not exist for this board (shouldn't get here, should be checked by caller)
        return;
    }

    // init the GPIO lines
    uint32_t mode = MP_HAL_PIN_MODE_ALT;
    uint32_t pull = spi->Init.CLKPolarity == SPI_POLARITY_LOW ? MP_HAL_PIN_PULL_DOWN : MP_HAL_PIN_PULL_UP;
    for (uint i = (enable_nss_pin ? 0 : 1); i < 4; i++) {
        if (pins[i] == NULL) {
            continue;
        }
        mp_hal_pin_config_alt(pins[i], mode, pull, AF_FN_SPI, (self - &spi_obj[0]) + 1);
    }

    // init the SPI device
    if (HAL_SPI_Init(spi) != HAL_OK) {
        // init error
        // TODO should raise an exception, but this function is not necessarily going to be
        // called via Python, so may not be properly wrapped in an NLR handler
        printf("OSError: HAL_SPI_Init failed\n");
        return;
    }

    // After calling HAL_SPI_Init() it seems that the DMA gets disconnected if
    // it was previously configured.  So we invalidate the DMA channel to force
    // an initialisation the next time we use it.
    dma_invalidate_channel(self->tx_dma_descr);
    dma_invalidate_channel(self->rx_dma_descr);
}