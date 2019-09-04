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
struct resv_map {int dummy; } ;
struct hstate {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  enum vma_resv_mode { ____Placeholder_vma_resv_mode } vma_resv_mode ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  HPAGE_RESV_OWNER ; 
#define  VMA_ADD_RESV 131 
#define  VMA_COMMIT_RESV 130 
#define  VMA_END_RESV 129 
#define  VMA_NEEDS_RESV 128 
 int VM_MAYSHARE ; 
 scalar_t__ is_vma_resv_set (struct vm_area_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  region_abort (struct resv_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long region_add (struct resv_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long region_chg (struct resv_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long region_del (struct resv_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vma_hugecache_offset (struct hstate*,struct vm_area_struct*,unsigned long) ; 
 struct resv_map* vma_resv_map (struct vm_area_struct*) ; 

__attribute__((used)) static long __vma_reservation_common(struct hstate *h,
				struct vm_area_struct *vma, unsigned long addr,
				enum vma_resv_mode mode)
{
	struct resv_map *resv;
	pgoff_t idx;
	long ret;

	resv = vma_resv_map(vma);
	if (!resv)
		return 1;

	idx = vma_hugecache_offset(h, vma, addr);
	switch (mode) {
	case VMA_NEEDS_RESV:
		ret = region_chg(resv, idx, idx + 1);
		break;
	case VMA_COMMIT_RESV:
		ret = region_add(resv, idx, idx + 1);
		break;
	case VMA_END_RESV:
		region_abort(resv, idx, idx + 1);
		ret = 0;
		break;
	case VMA_ADD_RESV:
		if (vma->vm_flags & VM_MAYSHARE)
			ret = region_add(resv, idx, idx + 1);
		else {
			region_abort(resv, idx, idx + 1);
			ret = region_del(resv, idx, idx + 1);
		}
		break;
	default:
		BUG();
	}

	if (vma->vm_flags & VM_MAYSHARE)
		return ret;
	else if (is_vma_resv_set(vma, HPAGE_RESV_OWNER) && ret >= 0) {
		/*
		 * In most cases, reserves always exist for private mappings.
		 * However, a file associated with mapping could have been
		 * hole punched or truncated after reserves were consumed.
		 * As subsequent fault on such a range will not use reserves.
		 * Subtle - The reserve map for private mappings has the
		 * opposite meaning than that of shared mappings.  If NO
		 * entry is in the reserve map, it means a reservation exists.
		 * If an entry exists in the reserve map, it means the
		 * reservation has already been consumed.  As a result, the
		 * return value of this routine is the opposite of the
		 * value returned from reserve map manipulation routines above.
		 */
		if (ret)
			return 0;
		else
			return 1;
	}
	else
		return ret < 0 ? ret : 0;
}