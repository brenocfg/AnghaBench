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
union jffs2_device_node {int /*<<< orphan*/  new_id; int /*<<< orphan*/  old_id; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_je16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_je32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_encode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  old_encode_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ old_valid_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int jffs2_encode_dev(union jffs2_device_node *jdev, dev_t rdev)
{
	if (old_valid_dev(rdev)) {
		jdev->old_id = cpu_to_je16(old_encode_dev(rdev));
		return sizeof(jdev->old_id);
	} else {
		jdev->new_id = cpu_to_je32(new_encode_dev(rdev));
		return sizeof(jdev->new_id);
	}
}