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
typedef  size_t u16 ;
struct TYPE_2__ {char const* name; } ;

/* Variables and functions */
 TYPE_1__* btrfs_csums ; 

const char *btrfs_super_csum_name(u16 csum_type)
{
	/* csum type is validated at mount time */
	return btrfs_csums[csum_type].name;
}