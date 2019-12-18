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
struct TYPE_2__ {int /*<<< orphan*/  wr_bytes_written; } ;
struct nfsd4_copy {int /*<<< orphan*/  nf_dst; int /*<<< orphan*/  nf_src; TYPE_1__ cp_res; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ _nfsd_copy_file_range (struct nfsd4_copy*) ; 
 int /*<<< orphan*/  nfs_ok ; 
 int /*<<< orphan*/  nfsd4_init_copy_res (struct nfsd4_copy*,int) ; 
 int /*<<< orphan*/  nfsd_file_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfserrno (scalar_t__) ; 

__attribute__((used)) static __be32 nfsd4_do_copy(struct nfsd4_copy *copy, bool sync)
{
	__be32 status;
	ssize_t bytes;

	bytes = _nfsd_copy_file_range(copy);
	/* for async copy, we ignore the error, client can always retry
	 * to get the error
	 */
	if (bytes < 0 && !copy->cp_res.wr_bytes_written)
		status = nfserrno(bytes);
	else {
		nfsd4_init_copy_res(copy, sync);
		status = nfs_ok;
	}

	nfsd_file_put(copy->nf_src);
	nfsd_file_put(copy->nf_dst);
	return status;
}