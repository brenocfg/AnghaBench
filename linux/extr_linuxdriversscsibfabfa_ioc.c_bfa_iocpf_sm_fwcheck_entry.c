#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct bfi_ioc_image_hdr_s {int /*<<< orphan*/  exec; } ;
struct bfa_iocpf_s {TYPE_2__* ioc; } ;
struct TYPE_9__ {int /*<<< orphan*/  ioc_init_sem_reg; int /*<<< orphan*/  smem_page_start; int /*<<< orphan*/  host_page_num_fn; int /*<<< orphan*/  smem_pg0; } ;
struct TYPE_10__ {TYPE_1__ ioc_regs; } ;

/* Variables and functions */
 scalar_t__ BFI_FWBOOT_TYPE_NORMAL ; 
 int BFI_IOC_UNINIT ; 
 int PSS_SMEM_PGNUM (int /*<<< orphan*/ ,int) ; 
 int PSS_SMEM_PGOFF (int) ; 
 int /*<<< orphan*/  bfa_ioc_fwver_get (TYPE_2__*,struct bfi_ioc_image_hdr_s*) ; 
 int bfa_ioc_get_cur_ioc_fwstate (TYPE_2__*) ; 
 int /*<<< orphan*/  bfa_ioc_hw_sem_get (TYPE_2__*) ; 
 int /*<<< orphan*/  bfa_ioc_ownership_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  bfa_ioc_set_alt_ioc_fwstate (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bfa_ioc_set_cur_ioc_fwstate (TYPE_2__*,int) ; 
 int /*<<< orphan*/  bfa_mem_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_2__*,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int swab32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_iocpf_sm_fwcheck_entry(struct bfa_iocpf_s *iocpf)
{
	struct bfi_ioc_image_hdr_s	fwhdr;
	u32	r32, fwstate, pgnum, pgoff, loff = 0;
	int	i;

	/*
	 * Spin on init semaphore to serialize.
	 */
	r32 = readl(iocpf->ioc->ioc_regs.ioc_init_sem_reg);
	while (r32 & 0x1) {
		udelay(20);
		r32 = readl(iocpf->ioc->ioc_regs.ioc_init_sem_reg);
	}

	/* h/w sem init */
	fwstate = bfa_ioc_get_cur_ioc_fwstate(iocpf->ioc);
	if (fwstate == BFI_IOC_UNINIT) {
		writel(1, iocpf->ioc->ioc_regs.ioc_init_sem_reg);
		goto sem_get;
	}

	bfa_ioc_fwver_get(iocpf->ioc, &fwhdr);

	if (swab32(fwhdr.exec) == BFI_FWBOOT_TYPE_NORMAL) {
		writel(1, iocpf->ioc->ioc_regs.ioc_init_sem_reg);
		goto sem_get;
	}

	/*
	 * Clear fwver hdr
	 */
	pgnum = PSS_SMEM_PGNUM(iocpf->ioc->ioc_regs.smem_pg0, loff);
	pgoff = PSS_SMEM_PGOFF(loff);
	writel(pgnum, iocpf->ioc->ioc_regs.host_page_num_fn);

	for (i = 0; i < sizeof(struct bfi_ioc_image_hdr_s) / sizeof(u32); i++) {
		bfa_mem_write(iocpf->ioc->ioc_regs.smem_page_start, loff, 0);
		loff += sizeof(u32);
	}

	bfa_trc(iocpf->ioc, fwstate);
	bfa_trc(iocpf->ioc, swab32(fwhdr.exec));
	bfa_ioc_set_cur_ioc_fwstate(iocpf->ioc, BFI_IOC_UNINIT);
	bfa_ioc_set_alt_ioc_fwstate(iocpf->ioc, BFI_IOC_UNINIT);

	/*
	 * Unlock the hw semaphore. Should be here only once per boot.
	 */
	bfa_ioc_ownership_reset(iocpf->ioc);

	/*
	 * unlock init semaphore.
	 */
	writel(1, iocpf->ioc->ioc_regs.ioc_init_sem_reg);

sem_get:
	bfa_ioc_hw_sem_get(iocpf->ioc);
}