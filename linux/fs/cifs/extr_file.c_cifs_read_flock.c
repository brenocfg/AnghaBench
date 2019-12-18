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
struct file_lock {int fl_flags; scalar_t__ fl_type; } ;
struct TCP_Server_Info {TYPE_1__* vals; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_2__ {int /*<<< orphan*/  shared_lock_type; int /*<<< orphan*/  exclusive_lock_type; int /*<<< orphan*/  unlock_lock_type; int /*<<< orphan*/  large_lock_type; } ;

/* Variables and functions */
 int FL_ACCESS ; 
 int FL_CLOSE ; 
 int FL_FLOCK ; 
 int FL_LEASE ; 
 int FL_OFDLCK ; 
 int FL_POSIX ; 
 int FL_SLEEP ; 
 int /*<<< orphan*/  FYI ; 
 scalar_t__ F_EXLCK ; 
 scalar_t__ F_RDLCK ; 
 scalar_t__ F_SHLCK ; 
 scalar_t__ F_UNLCK ; 
 scalar_t__ F_WRLCK ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
cifs_read_flock(struct file_lock *flock, __u32 *type, int *lock, int *unlock,
		bool *wait_flag, struct TCP_Server_Info *server)
{
	if (flock->fl_flags & FL_POSIX)
		cifs_dbg(FYI, "Posix\n");
	if (flock->fl_flags & FL_FLOCK)
		cifs_dbg(FYI, "Flock\n");
	if (flock->fl_flags & FL_SLEEP) {
		cifs_dbg(FYI, "Blocking lock\n");
		*wait_flag = true;
	}
	if (flock->fl_flags & FL_ACCESS)
		cifs_dbg(FYI, "Process suspended by mandatory locking - not implemented yet\n");
	if (flock->fl_flags & FL_LEASE)
		cifs_dbg(FYI, "Lease on file - not implemented yet\n");
	if (flock->fl_flags &
	    (~(FL_POSIX | FL_FLOCK | FL_SLEEP |
	       FL_ACCESS | FL_LEASE | FL_CLOSE | FL_OFDLCK)))
		cifs_dbg(FYI, "Unknown lock flags 0x%x\n", flock->fl_flags);

	*type = server->vals->large_lock_type;
	if (flock->fl_type == F_WRLCK) {
		cifs_dbg(FYI, "F_WRLCK\n");
		*type |= server->vals->exclusive_lock_type;
		*lock = 1;
	} else if (flock->fl_type == F_UNLCK) {
		cifs_dbg(FYI, "F_UNLCK\n");
		*type |= server->vals->unlock_lock_type;
		*unlock = 1;
		/* Check if unlock includes more than one lock range */
	} else if (flock->fl_type == F_RDLCK) {
		cifs_dbg(FYI, "F_RDLCK\n");
		*type |= server->vals->shared_lock_type;
		*lock = 1;
	} else if (flock->fl_type == F_EXLCK) {
		cifs_dbg(FYI, "F_EXLCK\n");
		*type |= server->vals->exclusive_lock_type;
		*lock = 1;
	} else if (flock->fl_type == F_SHLCK) {
		cifs_dbg(FYI, "F_SHLCK\n");
		*type |= server->vals->shared_lock_type;
		*lock = 1;
	} else
		cifs_dbg(FYI, "Unknown type of lock\n");
}