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
struct nfsd4_session {int dummy; } ;
struct nfs4_sessionid {int dummy; } ;
struct net {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 struct nfsd4_session* __find_in_sessionid_hashtbl (struct nfs4_sessionid*,struct net*) ; 
 scalar_t__ nfsd4_get_session_locked (struct nfsd4_session*) ; 
 scalar_t__ nfserr_badsession ; 

__attribute__((used)) static struct nfsd4_session *
find_in_sessionid_hashtbl(struct nfs4_sessionid *sessionid, struct net *net,
		__be32 *ret)
{
	struct nfsd4_session *session;
	__be32 status = nfserr_badsession;

	session = __find_in_sessionid_hashtbl(sessionid, net);
	if (!session)
		goto out;
	status = nfsd4_get_session_locked(session);
	if (status)
		session = NULL;
out:
	*ret = status;
	return session;
}