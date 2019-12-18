#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_6__ {void* beg; void* end; scalar_t__ formatted_node; } ;
typedef  TYPE_2__ reiserfs_blocknr_hint_t ;
typedef  void* b_blocknr_t ;
struct TYPE_5__ {int border; } ;
struct TYPE_7__ {TYPE_1__ s_alloc_options; } ;

/* Variables and functions */
 TYPE_4__* REISERFS_SB (struct super_block*) ; 
 int SB_BLOCK_COUNT (struct super_block*) ; 

__attribute__((used)) static inline void set_border_in_hint(struct super_block *s,
				      reiserfs_blocknr_hint_t * hint)
{
	b_blocknr_t border =
	    SB_BLOCK_COUNT(s) / REISERFS_SB(s)->s_alloc_options.border;

	if (hint->formatted_node)
		hint->end = border - 1;
	else
		hint->beg = border;
}