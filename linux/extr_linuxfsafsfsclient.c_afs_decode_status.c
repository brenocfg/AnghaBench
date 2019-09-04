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
struct afs_vnode {int /*<<< orphan*/  cb_lock; } ;
struct afs_read {int dummy; } ;
struct afs_file_status {int dummy; } ;
struct afs_call {int dummy; } ;
typedef  int /*<<< orphan*/  afs_dataversion_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 
 int xdr_decode_AFSFetchStatus (struct afs_call*,int /*<<< orphan*/  const**,struct afs_file_status*,struct afs_vnode*,int /*<<< orphan*/  const*,struct afs_read*) ; 

__attribute__((used)) static int afs_decode_status(struct afs_call *call,
			     const __be32 **_bp,
			     struct afs_file_status *status,
			     struct afs_vnode *vnode,
			     const afs_dataversion_t *expected_version,
			     struct afs_read *read_req)
{
	int ret;

	if (!vnode)
		return xdr_decode_AFSFetchStatus(call, _bp, status, vnode,
						 expected_version, read_req);

	write_seqlock(&vnode->cb_lock);
	ret = xdr_decode_AFSFetchStatus(call, _bp, status, vnode,
					expected_version, read_req);
	write_sequnlock(&vnode->cb_lock);
	return ret;
}