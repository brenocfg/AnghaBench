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
struct vm_area_struct {int vm_flags; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int GFP_TRANSHUGE ; 
 int GFP_TRANSHUGE_LIGHT ; 
 int /*<<< orphan*/  TRANSPARENT_HUGEPAGE_DEFRAG_DIRECT_FLAG ; 
 int /*<<< orphan*/  TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_FLAG ; 
 int /*<<< orphan*/  TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_OR_MADV_FLAG ; 
 int /*<<< orphan*/  TRANSPARENT_HUGEPAGE_DEFRAG_REQ_MADV_FLAG ; 
 int VM_HUGEPAGE ; 
 int __GFP_DIRECT_RECLAIM ; 
 int __GFP_KSWAPD_RECLAIM ; 
 int __GFP_NORETRY ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transparent_hugepage_flags ; 

__attribute__((used)) static inline gfp_t alloc_hugepage_direct_gfpmask(struct vm_area_struct *vma)
{
	const bool vma_madvised = !!(vma->vm_flags & VM_HUGEPAGE);

	/* Always do synchronous compaction */
	if (test_bit(TRANSPARENT_HUGEPAGE_DEFRAG_DIRECT_FLAG, &transparent_hugepage_flags))
		return GFP_TRANSHUGE | (vma_madvised ? 0 : __GFP_NORETRY);

	/* Kick kcompactd and fail quickly */
	if (test_bit(TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_FLAG, &transparent_hugepage_flags))
		return GFP_TRANSHUGE_LIGHT | __GFP_KSWAPD_RECLAIM;

	/* Synchronous compaction if madvised, otherwise kick kcompactd */
	if (test_bit(TRANSPARENT_HUGEPAGE_DEFRAG_KSWAPD_OR_MADV_FLAG, &transparent_hugepage_flags))
		return GFP_TRANSHUGE_LIGHT |
			(vma_madvised ? __GFP_DIRECT_RECLAIM :
					__GFP_KSWAPD_RECLAIM);

	/* Only do synchronous compaction if madvised */
	if (test_bit(TRANSPARENT_HUGEPAGE_DEFRAG_REQ_MADV_FLAG, &transparent_hugepage_flags))
		return GFP_TRANSHUGE_LIGHT |
		       (vma_madvised ? __GFP_DIRECT_RECLAIM : 0);

	return GFP_TRANSHUGE_LIGHT;
}