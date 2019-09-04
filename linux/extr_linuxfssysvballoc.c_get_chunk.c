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
typedef  int /*<<< orphan*/  sysv_zone_t ;
struct super_block {int dummy; } ;
struct buffer_head {char* b_data; } ;
struct TYPE_2__ {scalar_t__ s_type; } ;

/* Variables and functions */
 scalar_t__ FSTYPE_SYSV4 ; 
 TYPE_1__* SYSV_SB (struct super_block*) ; 

__attribute__((used)) static inline sysv_zone_t *get_chunk(struct super_block *sb, struct buffer_head *bh)
{
	char *bh_data = bh->b_data;

	if (SYSV_SB(sb)->s_type == FSTYPE_SYSV4)
		return (sysv_zone_t*)(bh_data+4);
	else
		return (sysv_zone_t*)(bh_data+2);
}