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
struct backing_dev_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int bdi_debug_register(struct backing_dev_info *bdi,
				      const char *name)
{
	return 0;
}