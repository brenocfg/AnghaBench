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
struct xdp_umem_fq_reuse {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (struct xdp_umem_fq_reuse*) ; 

void xsk_reuseq_free(struct xdp_umem_fq_reuse *rq)
{
	kvfree(rq);
}