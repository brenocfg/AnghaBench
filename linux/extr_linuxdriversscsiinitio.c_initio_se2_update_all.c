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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ i91udftNvRam ; 
 int /*<<< orphan*/  i91unvram ; 
 int /*<<< orphan*/ * i91unvramp ; 
 int /*<<< orphan*/  initio_se2_ew_ds (unsigned long) ; 
 int /*<<< orphan*/  initio_se2_ew_en (unsigned long) ; 
 int /*<<< orphan*/  initio_se2_wr (unsigned long,int,scalar_t__) ; 

__attribute__((used)) static void initio_se2_update_all(unsigned long base)
{				/* setup default pattern */
	int i;
	u16 chksum = 0;
	u16 *np, *np1;

	i91unvramp = &i91unvram;
	/* Calculate checksum first */
	np = (u16 *) i91udftNvRam;
	for (i = 0; i < 31; i++)
		chksum += *np++;
	*np = chksum;
	initio_se2_ew_en(base);	/* Enable write  */

	np = (u16 *) i91udftNvRam;
	np1 = (u16 *) i91unvramp;
	for (i = 0; i < 32; i++, np++, np1++) {
		if (*np != *np1)
			initio_se2_wr(base, i, *np);
	}
	initio_se2_ew_ds(base);	/* Disable write   */
}