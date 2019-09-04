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
struct TYPE_3__ {int len_addr; } ;
typedef  TYPE_1__ pxd_t ;
typedef  int __u32 ;

/* Variables and functions */
 int cpu_to_le32 (int) ; 

__attribute__((used)) static inline void PXDlength(pxd_t *pxd, __u32 len)
{
	pxd->len_addr = (pxd->len_addr & cpu_to_le32(~0xffffff)) |
			cpu_to_le32(len & 0xffffff);
}