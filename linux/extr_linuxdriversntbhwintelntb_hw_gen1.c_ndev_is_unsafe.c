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
struct intel_ntb_dev {unsigned long unsafe_flags; unsigned long unsafe_flags_ignore; } ;

/* Variables and functions */

__attribute__((used)) static inline int ndev_is_unsafe(struct intel_ntb_dev *ndev,
				 unsigned long flag)
{
	return !!(flag & ndev->unsafe_flags & ~ndev->unsafe_flags_ignore);
}