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
struct d_info_checkpoint {int /*<<< orphan*/  expansion; int /*<<< orphan*/  next_sub; int /*<<< orphan*/  next_comp; int /*<<< orphan*/  n; } ;
struct d_info {int /*<<< orphan*/  expansion; int /*<<< orphan*/  next_sub; int /*<<< orphan*/  next_comp; int /*<<< orphan*/  n; } ;

/* Variables and functions */

__attribute__((used)) static void
d_backtrack (struct d_info *di, struct d_info_checkpoint *checkpoint)
{
  di->n = checkpoint->n;
  di->next_comp = checkpoint->next_comp;
  di->next_sub = checkpoint->next_sub;
  di->expansion = checkpoint->expansion;
}