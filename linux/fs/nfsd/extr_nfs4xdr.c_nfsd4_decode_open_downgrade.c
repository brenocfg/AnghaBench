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
struct nfsd4_open_downgrade {int /*<<< orphan*/  od_share_deny; int /*<<< orphan*/  od_deleg_want; int /*<<< orphan*/  od_share_access; int /*<<< orphan*/  od_seqid; int /*<<< orphan*/  od_stateid; } ;
struct nfsd4_compoundargs {int dummy; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DECODE_HEAD ; 
 int /*<<< orphan*/  DECODE_TAIL ; 
 int /*<<< orphan*/  READ_BUF (int) ; 
 int /*<<< orphan*/  be32_to_cpup (int /*<<< orphan*/ ) ; 
 scalar_t__ nfsd4_decode_share_access (struct nfsd4_compoundargs*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nfsd4_decode_share_deny (struct nfsd4_compoundargs*,int /*<<< orphan*/ *) ; 
 scalar_t__ nfsd4_decode_stateid (struct nfsd4_compoundargs*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p ; 
 scalar_t__ status ; 

__attribute__((used)) static __be32
nfsd4_decode_open_downgrade(struct nfsd4_compoundargs *argp, struct nfsd4_open_downgrade *open_down)
{
	DECODE_HEAD;
		    
	status = nfsd4_decode_stateid(argp, &open_down->od_stateid);
	if (status)
		return status;
	READ_BUF(4);
	open_down->od_seqid = be32_to_cpup(p++);
	status = nfsd4_decode_share_access(argp, &open_down->od_share_access,
					   &open_down->od_deleg_want, NULL);
	if (status)
		return status;
	status = nfsd4_decode_share_deny(argp, &open_down->od_share_deny);
	if (status)
		return status;
	DECODE_TAIL;
}