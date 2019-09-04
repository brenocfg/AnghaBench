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
typedef  int /*<<< orphan*/  u32 ;
struct sisl_rht_entry_f1 {int valid; int /*<<< orphan*/  dw; int /*<<< orphan*/  port_sel; void* fp; int /*<<< orphan*/  lun_id; int /*<<< orphan*/  member_0; } ;
struct sisl_rht_entry {int dummy; } ;

/* Variables and functions */
 void* SISL_RHT_FP (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  memset (struct sisl_rht_entry_f1*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rht_format1(struct sisl_rht_entry *rhte, u64 lun_id, u32 perm,
			u32 port_sel)
{
	/*
	 * Populate the Format 1 RHT entry for direct access (physical
	 * LUN) using the synchronization sequence defined in the
	 * SISLite specification.
	 */
	struct sisl_rht_entry_f1 dummy = { 0 };
	struct sisl_rht_entry_f1 *rhte_f1 = (struct sisl_rht_entry_f1 *)rhte;

	memset(rhte_f1, 0, sizeof(*rhte_f1));
	rhte_f1->fp = SISL_RHT_FP(1U, 0);
	dma_wmb(); /* Make setting of format bit visible */

	rhte_f1->lun_id = lun_id;
	dma_wmb(); /* Make setting of LUN id visible */

	/*
	 * Use a dummy RHT Format 1 entry to build the second dword
	 * of the entry that must be populated in a single write when
	 * enabled (valid bit set to TRUE).
	 */
	dummy.valid = 0x80;
	dummy.fp = SISL_RHT_FP(1U, perm);
	dummy.port_sel = port_sel;
	rhte_f1->dw = dummy.dw;

	dma_wmb(); /* Make remaining RHT entry fields visible */
}