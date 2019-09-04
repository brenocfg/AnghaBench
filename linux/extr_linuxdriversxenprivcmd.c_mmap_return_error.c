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
typedef  int xen_pfn_t ;
struct mmap_batch_state {int version; int /*<<< orphan*/  user_err; int /*<<< orphan*/  user_gfn; } ;

/* Variables and functions */
 int ENOENT ; 
 int PRIVCMD_MMAPBATCH_MFN_ERROR ; 
 int PRIVCMD_MMAPBATCH_PAGED_ERROR ; 
 int __put_user (int,int /*<<< orphan*/ ) ; 
 int get_user (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mmap_return_error(int err, struct mmap_batch_state *st)
{
	int ret;

	if (st->version == 1) {
		if (err) {
			xen_pfn_t gfn;

			ret = get_user(gfn, st->user_gfn);
			if (ret < 0)
				return ret;
			/*
			 * V1 encodes the error codes in the 32bit top
			 * nibble of the gfn (with its known
			 * limitations vis-a-vis 64 bit callers).
			 */
			gfn |= (err == -ENOENT) ?
				PRIVCMD_MMAPBATCH_PAGED_ERROR :
				PRIVCMD_MMAPBATCH_MFN_ERROR;
			return __put_user(gfn, st->user_gfn++);
		} else
			st->user_gfn++;
	} else { /* st->version == 2 */
		if (err)
			return __put_user(err, st->user_err++);
		else
			st->user_err++;
	}

	return 0;
}