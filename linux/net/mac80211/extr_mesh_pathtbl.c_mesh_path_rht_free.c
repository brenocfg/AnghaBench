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
struct mesh_table {int dummy; } ;
struct mesh_path {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mesh_path_free_rcu (struct mesh_table*,struct mesh_path*) ; 

__attribute__((used)) static void mesh_path_rht_free(void *ptr, void *tblptr)
{
	struct mesh_path *mpath = ptr;
	struct mesh_table *tbl = tblptr;

	mesh_path_free_rcu(tbl, mpath);
}