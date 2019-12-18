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
struct hfs_extent {scalar_t__ count; scalar_t__ block; } ;

/* Variables and functions */
 scalar_t__ be16_to_cpu (scalar_t__) ; 

__attribute__((used)) static u16 hfs_ext_lastblock(struct hfs_extent *ext)
{
	int i;

	ext += 2;
	for (i = 0; i < 2; ext--, i++)
		if (ext->count)
			break;
	return be16_to_cpu(ext->block) + be16_to_cpu(ext->count);
}