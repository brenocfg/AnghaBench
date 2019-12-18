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
typedef  int __u64 ;
struct TYPE_2__ {int mask_val; int /*<<< orphan*/  keyword; } ;

/* Variables and functions */
 TYPE_1__* s_kmod_keyword_mask_map ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void do_k_mask(int i, char *unchecked_keyword, __u64 **sane_mask)
{

	if (!strcmp(s_kmod_keyword_mask_map[i].keyword, unchecked_keyword))
		**sane_mask = (**sane_mask) |
				s_kmod_keyword_mask_map[i].mask_val;
}