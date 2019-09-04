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
struct mesh_table {int /*<<< orphan*/  rhead; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mesh_table*) ; 
 int /*<<< orphan*/  mesh_path_rht_free ; 
 int /*<<< orphan*/  rhashtable_free_and_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mesh_table*) ; 

__attribute__((used)) static void mesh_table_free(struct mesh_table *tbl)
{
	rhashtable_free_and_destroy(&tbl->rhead,
				    mesh_path_rht_free, tbl);
	kfree(tbl);
}