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
struct nfsd4_session {int /*<<< orphan*/  se_flags; int /*<<< orphan*/  se_ref; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_SESSION_DEAD ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfserr_jukebox ; 

__attribute__((used)) static __be32 mark_session_dead_locked(struct nfsd4_session *ses, int ref_held_by_me)
{
	if (atomic_read(&ses->se_ref) > ref_held_by_me)
		return nfserr_jukebox;
	ses->se_flags |= NFS4_SESSION_DEAD;
	return nfs_ok;
}