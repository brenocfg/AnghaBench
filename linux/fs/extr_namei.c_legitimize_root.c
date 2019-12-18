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
struct TYPE_2__ {int /*<<< orphan*/  mnt; } ;
struct nameidata {int flags; int /*<<< orphan*/  root_seq; TYPE_1__ root; } ;

/* Variables and functions */
 int LOOKUP_ROOT ; 
 int LOOKUP_ROOT_GRABBED ; 
 int legitimize_path (struct nameidata*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool legitimize_root(struct nameidata *nd)
{
	if (!nd->root.mnt || (nd->flags & LOOKUP_ROOT))
		return true;
	nd->flags |= LOOKUP_ROOT_GRABBED;
	return legitimize_path(nd, &nd->root, nd->root_seq);
}