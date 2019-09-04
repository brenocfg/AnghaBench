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
struct afs_volume {int /*<<< orphan*/  usage; int /*<<< orphan*/  name; } ;
struct afs_cell {int /*<<< orphan*/  net; } ;

/* Variables and functions */
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_destroy_volume (int /*<<< orphan*/ ,struct afs_volume*) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 

void afs_put_volume(struct afs_cell *cell, struct afs_volume *volume)
{
	if (volume) {
		_enter("%s", volume->name);

		if (atomic_dec_and_test(&volume->usage))
			afs_destroy_volume(cell->net, volume);
	}
}