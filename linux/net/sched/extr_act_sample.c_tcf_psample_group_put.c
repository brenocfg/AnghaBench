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
struct psample_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  psample_group_put (struct psample_group*) ; 

__attribute__((used)) static void tcf_psample_group_put(void *priv)
{
	struct psample_group *group = priv;

	psample_group_put(group);
}