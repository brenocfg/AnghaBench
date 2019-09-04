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
typedef  int /*<<< orphan*/  u32 ;
struct svc_rqst {int dummy; } ;
struct nfsd4_create_session {int flags; } ;
struct nfsd4_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS4_CDFC4_BACK ; 
 int /*<<< orphan*/  NFS4_CDFC4_FORE ; 
 int SESSION4_BACK_CHAN ; 
 struct nfsd4_conn* alloc_conn (struct svc_rqst*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfsd4_conn *alloc_conn_from_crses(struct svc_rqst *rqstp, struct nfsd4_create_session *cses)
{
	u32 dir = NFS4_CDFC4_FORE;

	if (cses->flags & SESSION4_BACK_CHAN)
		dir |= NFS4_CDFC4_BACK;
	return alloc_conn(rqstp, dir);
}