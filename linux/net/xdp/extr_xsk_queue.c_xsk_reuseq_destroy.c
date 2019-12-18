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
struct xdp_umem {int /*<<< orphan*/ * fq_reuse; } ;

/* Variables and functions */
 int /*<<< orphan*/  xsk_reuseq_free (int /*<<< orphan*/ *) ; 

void xsk_reuseq_destroy(struct xdp_umem *umem)
{
	xsk_reuseq_free(umem->fq_reuse);
	umem->fq_reuse = NULL;
}