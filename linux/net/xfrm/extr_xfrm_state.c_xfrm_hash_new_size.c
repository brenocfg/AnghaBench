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
struct hlist_head {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long xfrm_hash_new_size(unsigned int state_hmask)
{
	return ((state_hmask + 1) << 1) * sizeof(struct hlist_head);
}