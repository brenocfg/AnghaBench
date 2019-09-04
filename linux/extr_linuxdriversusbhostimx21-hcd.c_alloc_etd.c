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
struct imx21 {struct etd_priv* etd; } ;
struct etd_priv {int alloc; } ;

/* Variables and functions */
 int USB_NUM_ETD ; 
 int /*<<< orphan*/  debug_etd_allocated (struct imx21*) ; 
 int /*<<< orphan*/  memset (struct etd_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int alloc_etd(struct imx21 *imx21)
{
	int i;
	struct etd_priv *etd = imx21->etd;

	for (i = 0; i < USB_NUM_ETD; i++, etd++) {
		if (etd->alloc == 0) {
			memset(etd, 0, sizeof(imx21->etd[0]));
			etd->alloc = 1;
			debug_etd_allocated(imx21);
			return i;
		}
	}
	return -1;
}