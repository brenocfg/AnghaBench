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
struct p9_trans_module {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 

void v9fs_put_trans(struct p9_trans_module *m)
{
	if (m)
		module_put(m->owner);
}