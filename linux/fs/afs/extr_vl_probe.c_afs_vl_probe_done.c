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
struct afs_vlserver {int /*<<< orphan*/  flags; int /*<<< orphan*/  probe_outstanding; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_VLSERVER_FL_PROBING ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_var (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool afs_vl_probe_done(struct afs_vlserver *server)
{
	if (!atomic_dec_and_test(&server->probe_outstanding))
		return false;

	wake_up_var(&server->probe_outstanding);
	clear_bit_unlock(AFS_VLSERVER_FL_PROBING, &server->flags);
	wake_up_bit(&server->flags, AFS_VLSERVER_FL_PROBING);
	return true;
}