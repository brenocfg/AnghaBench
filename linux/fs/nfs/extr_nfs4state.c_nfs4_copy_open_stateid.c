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
struct nfs4_state {int /*<<< orphan*/  open_stateid; int /*<<< orphan*/  flags; int /*<<< orphan*/  seqlock; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_OPEN_STATE ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int read_seqbegin (int /*<<< orphan*/ *) ; 
 scalar_t__ read_seqretry (int /*<<< orphan*/ *,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zero_stateid ; 

bool nfs4_copy_open_stateid(nfs4_stateid *dst, struct nfs4_state *state)
{
	bool ret;
	const nfs4_stateid *src;
	int seq;

	do {
		ret = false;
		src = &zero_stateid;
		seq = read_seqbegin(&state->seqlock);
		if (test_bit(NFS_OPEN_STATE, &state->flags)) {
			src = &state->open_stateid;
			ret = true;
		}
		nfs4_stateid_copy(dst, src);
	} while (read_seqretry(&state->seqlock, seq));
	return ret;
}