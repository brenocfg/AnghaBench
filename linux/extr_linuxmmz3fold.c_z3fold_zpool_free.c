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
 int /*<<< orphan*/  z3fold_free (void*,unsigned long) ; 

__attribute__((used)) static void z3fold_zpool_free(void *pool, unsigned long handle)
{
	z3fold_free(pool, handle);
}