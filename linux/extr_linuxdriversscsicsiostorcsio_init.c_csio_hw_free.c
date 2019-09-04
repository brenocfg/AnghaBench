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
struct csio_hw {int /*<<< orphan*/  regstart; } ;

/* Variables and functions */
 int /*<<< orphan*/  csio_dfs_destroy (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_exit (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_hw_exit_workers (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_intr_disable (struct csio_hw*,int) ; 
 int /*<<< orphan*/  csio_resource_free (struct csio_hw*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct csio_hw*) ; 

__attribute__((used)) static void
csio_hw_free(struct csio_hw *hw)
{
	csio_intr_disable(hw, true);
	csio_hw_exit_workers(hw);
	csio_hw_exit(hw);
	iounmap(hw->regstart);
	csio_dfs_destroy(hw);
	csio_resource_free(hw);
	kfree(hw);
}