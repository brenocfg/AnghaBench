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
struct nfsd4_compoundargs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct nfsd4_bind_conn_to_session {int /*<<< orphan*/  dir; TYPE_1__ sessionid; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  COPYMEM (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 scalar_t__ NFS4_MAX_SESSIONID_LEN ; 
 int /*<<< orphan*/  READ_BUF (scalar_t__) ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p ; 

__attribute__((used)) static __be32 nfsd4_decode_bind_conn_to_session(struct nfsd4_compoundargs *argp, struct nfsd4_bind_conn_to_session *bcts)
{
	DECODE_HEAD;

	READ_BUF(NFS4_MAX_SESSIONID_LEN + 8);
	COPYMEM(bcts->sessionid.data, NFS4_MAX_SESSIONID_LEN);
	bcts->dir = be32_to_cpup(p++);
	/* XXX: skipping ctsa_use_conn_in_rdma_mode.  Perhaps Tom Tucker
	 * could help us figure out we should be using it. */
	DECODE_TAIL;
}