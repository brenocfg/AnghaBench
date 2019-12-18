#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  Instance; } ;
struct TYPE_11__ {int /*<<< orphan*/  Instance; } ;
struct TYPE_10__ {int /*<<< orphan*/  Instance; } ;
struct TYPE_9__ {int /*<<< orphan*/  Instance; } ;
struct TYPE_8__ {int /*<<< orphan*/  Instance; } ;
struct TYPE_7__ {int /*<<< orphan*/  Instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI1 ; 
 int /*<<< orphan*/  SPI2 ; 
 int /*<<< orphan*/  SPI3 ; 
 int /*<<< orphan*/  SPI4 ; 
 int /*<<< orphan*/  SPI5 ; 
 int /*<<< orphan*/  SPI6 ; 
 TYPE_6__ SPIHandle1 ; 
 TYPE_5__ SPIHandle2 ; 
 TYPE_4__ SPIHandle3 ; 
 TYPE_3__ SPIHandle4 ; 
 TYPE_2__ SPIHandle5 ; 
 TYPE_1__ SPIHandle6 ; 

void spi_init0(void) {
    // Initialise the SPI handles.
    // The structs live on the BSS so all other fields will be zero after a reset.
    #if defined(MICROPY_HW_SPI1_SCK)
    SPIHandle1.Instance = SPI1;
    #endif
    #if defined(MICROPY_HW_SPI2_SCK)
    SPIHandle2.Instance = SPI2;
    #endif
    #if defined(MICROPY_HW_SPI3_SCK)
    SPIHandle3.Instance = SPI3;
    #endif
    #if defined(MICROPY_HW_SPI4_SCK)
    SPIHandle4.Instance = SPI4;
    #endif
    #if defined(MICROPY_HW_SPI5_SCK)
    SPIHandle5.Instance = SPI5;
    #endif
    #if defined(MICROPY_HW_SPI6_SCK)
    SPIHandle6.Instance = SPI6;
    #endif
}