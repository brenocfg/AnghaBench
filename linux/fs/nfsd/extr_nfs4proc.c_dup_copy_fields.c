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
struct nfsd4_copy {int /*<<< orphan*/  cp_stateid; void* nf_src; void* nf_dst; int /*<<< orphan*/  cp_clp; int /*<<< orphan*/  fh; int /*<<< orphan*/  cp_res; int /*<<< orphan*/  cp_synchronous; int /*<<< orphan*/  cp_count; int /*<<< orphan*/  cp_dst_pos; int /*<<< orphan*/  cp_src_pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* nfsd_file_get (void*) ; 

__attribute__((used)) static void dup_copy_fields(struct nfsd4_copy *src, struct nfsd4_copy *dst)
{
	dst->cp_src_pos = src->cp_src_pos;
	dst->cp_dst_pos = src->cp_dst_pos;
	dst->cp_count = src->cp_count;
	dst->cp_synchronous = src->cp_synchronous;
	memcpy(&dst->cp_res, &src->cp_res, sizeof(src->cp_res));
	memcpy(&dst->fh, &src->fh, sizeof(src->fh));
	dst->cp_clp = src->cp_clp;
	dst->nf_dst = nfsd_file_get(src->nf_dst);
	dst->nf_src = nfsd_file_get(src->nf_src);
	memcpy(&dst->cp_stateid, &src->cp_stateid, sizeof(src->cp_stateid));
}