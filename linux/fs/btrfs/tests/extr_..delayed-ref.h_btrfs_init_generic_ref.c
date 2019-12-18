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
typedef  void* u64 ;
struct btrfs_ref {int action; void* parent; void* len; void* bytenr; } ;

/* Variables and functions */

__attribute__((used)) static inline void btrfs_init_generic_ref(struct btrfs_ref *generic_ref,
				int action, u64 bytenr, u64 len, u64 parent)
{
	generic_ref->action = action;
	generic_ref->bytenr = bytenr;
	generic_ref->len = len;
	generic_ref->parent = parent;
}