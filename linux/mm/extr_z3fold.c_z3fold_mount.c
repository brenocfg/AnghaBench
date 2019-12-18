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

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kern_mount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  z3fold_fs ; 
 int /*<<< orphan*/  z3fold_mnt ; 

__attribute__((used)) static int z3fold_mount(void)
{
	int ret = 0;

	z3fold_mnt = kern_mount(&z3fold_fs);
	if (IS_ERR(z3fold_mnt))
		ret = PTR_ERR(z3fold_mnt);

	return ret;
}