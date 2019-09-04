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
struct nfsd4_session {int /*<<< orphan*/  se_ref; int /*<<< orphan*/  se_client; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ get_client_locked (int /*<<< orphan*/ ) ; 
 scalar_t__ is_session_dead (struct nfsd4_session*) ; 
 scalar_t__ nfs_ok ; 
 scalar_t__ nfserr_badsession ; 

__attribute__((used)) static __be32 nfsd4_get_session_locked(struct nfsd4_session *ses)
{
	__be32 status;

	if (is_session_dead(ses))
		return nfserr_badsession;
	status = get_client_locked(ses->se_client);
	if (status)
		return status;
	atomic_inc(&ses->se_ref);
	return nfs_ok;
}