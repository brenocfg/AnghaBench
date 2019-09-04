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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct sfp_mem_s {int dummy; } ;
struct bfa_sfp_s {int /*<<< orphan*/ * dbuf_kva; int /*<<< orphan*/  dbuf_pa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_DMA_ALIGN_SZ ; 
 scalar_t__ BFA_ROUNDUP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
bfa_sfp_memclaim(struct bfa_sfp_s *sfp, u8 *dm_kva, u64 dm_pa)
{
	sfp->dbuf_kva   = dm_kva;
	sfp->dbuf_pa    = dm_pa;
	memset(sfp->dbuf_kva, 0, sizeof(struct sfp_mem_s));

	dm_kva += BFA_ROUNDUP(sizeof(struct sfp_mem_s), BFA_DMA_ALIGN_SZ);
	dm_pa += BFA_ROUNDUP(sizeof(struct sfp_mem_s), BFA_DMA_ALIGN_SZ);
}