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
typedef  void* u64 ;
struct TYPE_2__ {void* offset; void* ino; void* ref_root; } ;
struct btrfs_ref {int /*<<< orphan*/  type; TYPE_1__ data_ref; void* real_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_REF_DATA ; 

__attribute__((used)) static inline void btrfs_init_data_ref(struct btrfs_ref *generic_ref,
				u64 ref_root, u64 ino, u64 offset)
{
	/* If @real_root not set, use @root as fallback */
	if (!generic_ref->real_root)
		generic_ref->real_root = ref_root;
	generic_ref->data_ref.ref_root = ref_root;
	generic_ref->data_ref.ino = ino;
	generic_ref->data_ref.offset = offset;
	generic_ref->type = BTRFS_REF_DATA;
}