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
struct ffs_data {int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENTER () ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ffs_data_get(struct ffs_data *ffs)
{
	ENTER();

	refcount_inc(&ffs->ref);
}