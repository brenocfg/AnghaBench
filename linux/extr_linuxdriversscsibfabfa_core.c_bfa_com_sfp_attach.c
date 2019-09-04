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
struct bfa_sfp_s {int dummy; } ;
struct bfa_s {int /*<<< orphan*/  trcmod; int /*<<< orphan*/  ioc; } ;
struct bfa_mem_dma_s {int /*<<< orphan*/  dma_curp; int /*<<< orphan*/  kva_curp; } ;

/* Variables and functions */
 struct bfa_mem_dma_s* BFA_MEM_SFP_DMA (struct bfa_s*) ; 
 struct bfa_sfp_s* BFA_SFP_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_sfp_attach (struct bfa_sfp_s*,int /*<<< orphan*/ *,struct bfa_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sfp_memclaim (struct bfa_sfp_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_com_sfp_attach(struct bfa_s *bfa)
{
	struct bfa_sfp_s	*sfp = BFA_SFP_MOD(bfa);
	struct bfa_mem_dma_s	*sfp_dma = BFA_MEM_SFP_DMA(bfa);

	bfa_sfp_attach(sfp, &bfa->ioc, bfa, bfa->trcmod);
	bfa_sfp_memclaim(sfp, sfp_dma->kva_curp, sfp_dma->dma_curp);
}