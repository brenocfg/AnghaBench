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
typedef  scalar_t__ u8 ;
struct orc_host {int dummy; } ;
struct TYPE_2__ {scalar_t__ CheckSum; } ;

/* Variables and functions */
 TYPE_1__* nvramp ; 
 scalar_t__ orc_nv_read (struct orc_host*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int se2_rd_all(struct orc_host * host)
{
	int i;
	u8 *np, chksum = 0;

	np = (u8 *) nvramp;
	for (i = 0; i < 64; i++, np++) {	/* <01> */
		if (orc_nv_read(host, (u8) i, np) == 0)
			return -1;
	}

	/*------ Is ckecksum ok ? ------*/
	np = (u8 *) nvramp;
	for (i = 0; i < 63; i++)
		chksum += *np++;

	if (nvramp->CheckSum != (u8) chksum)
		return -1;
	return 1;
}