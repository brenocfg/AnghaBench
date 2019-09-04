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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ le32_to_cpu (scalar_t__) ; 

void
lpfc_sli_pcimem_bcopy(void *srcp, void *destp, uint32_t cnt)
{
	uint32_t *src = srcp;
	uint32_t *dest = destp;
	uint32_t ldata;
	int i;

	for (i = 0; i < (int)cnt; i += sizeof (uint32_t)) {
		ldata = *src;
		ldata = le32_to_cpu(ldata);
		*dest = ldata;
		src++;
		dest++;
	}
}