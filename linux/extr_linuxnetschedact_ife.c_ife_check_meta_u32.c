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
typedef  scalar_t__ u32 ;
struct tcf_meta_info {scalar_t__ metaval; } ;

/* Variables and functions */

int ife_check_meta_u32(u32 metaval, struct tcf_meta_info *mi)
{
	if (metaval || mi->metaval)
		return 8; /* T+L+V == 2+2+4 */

	return 0;
}