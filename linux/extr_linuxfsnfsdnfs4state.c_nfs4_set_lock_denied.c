#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ cl_id; scalar_t__ cl_boot; } ;
struct TYPE_9__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;
struct nfsd4_lock_denied {scalar_t__ ld_start; scalar_t__ ld_length; int /*<<< orphan*/  ld_type; TYPE_5__ ld_clientid; TYPE_4__ ld_owner; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_2__* so_client; TYPE_1__ so_owner; } ;
struct nfs4_lockowner {TYPE_3__ lo_owner; } ;
struct file_lock {scalar_t__ fl_start; scalar_t__ fl_end; scalar_t__ fl_type; scalar_t__ fl_owner; int /*<<< orphan*/ * fl_lmops; } ;
struct TYPE_7__ {TYPE_5__ cl_clientid; } ;

/* Variables and functions */
 scalar_t__ F_RDLCK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NFS4_MAX_UINT64 ; 
 int /*<<< orphan*/  NFS4_READ_LT ; 
 int /*<<< orphan*/  NFS4_WRITE_LT ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_posix_mng_ops ; 

__attribute__((used)) static inline void
nfs4_set_lock_denied(struct file_lock *fl, struct nfsd4_lock_denied *deny)
{
	struct nfs4_lockowner *lo;

	if (fl->fl_lmops == &nfsd_posix_mng_ops) {
		lo = (struct nfs4_lockowner *) fl->fl_owner;
		deny->ld_owner.data = kmemdup(lo->lo_owner.so_owner.data,
					lo->lo_owner.so_owner.len, GFP_KERNEL);
		if (!deny->ld_owner.data)
			/* We just don't care that much */
			goto nevermind;
		deny->ld_owner.len = lo->lo_owner.so_owner.len;
		deny->ld_clientid = lo->lo_owner.so_client->cl_clientid;
	} else {
nevermind:
		deny->ld_owner.len = 0;
		deny->ld_owner.data = NULL;
		deny->ld_clientid.cl_boot = 0;
		deny->ld_clientid.cl_id = 0;
	}
	deny->ld_start = fl->fl_start;
	deny->ld_length = NFS4_MAX_UINT64;
	if (fl->fl_end != NFS4_MAX_UINT64)
		deny->ld_length = fl->fl_end - fl->fl_start + 1;        
	deny->ld_type = NFS4_READ_LT;
	if (fl->fl_type != F_RDLCK)
		deny->ld_type = NFS4_WRITE_LT;
}