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
typedef  int /*<<< orphan*/  u64 ;
struct xdp_umem_fq_reuse {scalar_t__ nentries; scalar_t__ length; int /*<<< orphan*/  handles; } ;
struct xdp_umem {struct xdp_umem_fq_reuse* fq_reuse; } ;

/* Variables and functions */
 int /*<<< orphan*/  array_size (scalar_t__,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct xdp_umem_fq_reuse *xsk_reuseq_swap(struct xdp_umem *umem,
					  struct xdp_umem_fq_reuse *newq)
{
	struct xdp_umem_fq_reuse *oldq = umem->fq_reuse;

	if (!oldq) {
		umem->fq_reuse = newq;
		return NULL;
	}

	if (newq->nentries < oldq->length)
		return newq;

	memcpy(newq->handles, oldq->handles,
	       array_size(oldq->length, sizeof(u64)));
	newq->length = oldq->length;

	umem->fq_reuse = newq;
	return oldq;
}