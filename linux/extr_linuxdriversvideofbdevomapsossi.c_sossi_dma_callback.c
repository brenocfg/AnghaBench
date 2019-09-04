#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lcdc_callback_data; int /*<<< orphan*/  (* lcdc_callback ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  fck; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_stop_lcd_dma () ; 
 TYPE_1__ sossi ; 
 int /*<<< orphan*/  sossi_stop_transfer () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sossi_dma_callback(void *data)
{
	omap_stop_lcd_dma();
	sossi_stop_transfer();
	clk_disable(sossi.fck);
	sossi.lcdc_callback(sossi.lcdc_callback_data);
}