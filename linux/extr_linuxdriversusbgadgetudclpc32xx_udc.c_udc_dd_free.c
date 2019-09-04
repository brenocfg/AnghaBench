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
struct lpc32xx_usbd_dd_gad {int /*<<< orphan*/  this_dma; } ;
struct lpc32xx_udc {int /*<<< orphan*/  dd_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct lpc32xx_usbd_dd_gad*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void udc_dd_free(struct lpc32xx_udc *udc, struct lpc32xx_usbd_dd_gad *dd)
{
	dma_pool_free(udc->dd_cache, dd, dd->this_dma);
}