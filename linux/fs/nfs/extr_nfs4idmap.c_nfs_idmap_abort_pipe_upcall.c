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
struct idmap {int /*<<< orphan*/ * idmap_upcall_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_idmap_complete_pipe_upcall_locked (struct idmap*,int) ; 

__attribute__((used)) static void
nfs_idmap_abort_pipe_upcall(struct idmap *idmap, int ret)
{
	if (idmap->idmap_upcall_data != NULL)
		nfs_idmap_complete_pipe_upcall_locked(idmap, ret);
}