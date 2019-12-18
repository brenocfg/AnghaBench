#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int guest_phys_addr; int memory_size; int slot; int flags; uintptr_t userspace_addr; } ;
struct userspace_mem_region {int mmap_size; struct userspace_mem_region* next; struct userspace_mem_region* prev; TYPE_1__ region; scalar_t__ host_mem; int /*<<< orphan*/  unused_phy_pages; int /*<<< orphan*/  mmap_start; } ;
struct kvm_vm {size_t page_size; int page_shift; int max_gfn; struct userspace_mem_region* userspace_mem_region_head; int /*<<< orphan*/  fd; } ;
typedef  enum vm_mem_backing_src_type { ____Placeholder_vm_mem_backing_src_type } vm_mem_backing_src_type ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_SET_USER_MEMORY_REGION ; 
 size_t KVM_UTIL_PGS_PER_HUGEPG ; 
 int /*<<< orphan*/  MADV_HUGEPAGE ; 
 int /*<<< orphan*/  MADV_NOHUGEPAGE ; 
 int MAP_ANONYMOUS ; 
 int /*<<< orphan*/  MAP_FAILED ; 
 int MAP_HUGETLB ; 
 int MAP_PRIVATE ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  TEST_ASSERT (int,char*,...) ; 
 int VM_MEM_SRC_ANONYMOUS ; 
 int VM_MEM_SRC_ANONYMOUS_HUGETLB ; 
 int VM_MEM_SRC_ANONYMOUS_THP ; 
 scalar_t__ align (int /*<<< orphan*/ ,size_t) ; 
 struct userspace_mem_region* calloc (int,int) ; 
 int errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int madvise (scalar_t__,int,int /*<<< orphan*/ ) ; 
 size_t max (size_t,size_t) ; 
 int /*<<< orphan*/  mmap (int /*<<< orphan*/ *,size_t,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparsebit_alloc () ; 
 int /*<<< orphan*/  sparsebit_set_num (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ userspace_mem_region_find (struct kvm_vm*,int,int) ; 

void vm_userspace_mem_region_add(struct kvm_vm *vm,
	enum vm_mem_backing_src_type src_type,
	uint64_t guest_paddr, uint32_t slot, uint64_t npages,
	uint32_t flags)
{
	int ret;
	struct userspace_mem_region *region;
	size_t huge_page_size = KVM_UTIL_PGS_PER_HUGEPG * vm->page_size;
	size_t alignment;

	TEST_ASSERT((guest_paddr % vm->page_size) == 0, "Guest physical "
		"address not on a page boundary.\n"
		"  guest_paddr: 0x%lx vm->page_size: 0x%x",
		guest_paddr, vm->page_size);
	TEST_ASSERT((((guest_paddr >> vm->page_shift) + npages) - 1)
		<= vm->max_gfn, "Physical range beyond maximum "
		"supported physical address,\n"
		"  guest_paddr: 0x%lx npages: 0x%lx\n"
		"  vm->max_gfn: 0x%lx vm->page_size: 0x%x",
		guest_paddr, npages, vm->max_gfn, vm->page_size);

	/*
	 * Confirm a mem region with an overlapping address doesn't
	 * already exist.
	 */
	region = (struct userspace_mem_region *) userspace_mem_region_find(
		vm, guest_paddr, (guest_paddr + npages * vm->page_size) - 1);
	if (region != NULL)
		TEST_ASSERT(false, "overlapping userspace_mem_region already "
			"exists\n"
			"  requested guest_paddr: 0x%lx npages: 0x%lx "
			"page_size: 0x%x\n"
			"  existing guest_paddr: 0x%lx size: 0x%lx",
			guest_paddr, npages, vm->page_size,
			(uint64_t) region->region.guest_phys_addr,
			(uint64_t) region->region.memory_size);

	/* Confirm no region with the requested slot already exists. */
	for (region = vm->userspace_mem_region_head; region;
		region = region->next) {
		if (region->region.slot == slot)
			break;
	}
	if (region != NULL)
		TEST_ASSERT(false, "A mem region with the requested slot "
			"already exists.\n"
			"  requested slot: %u paddr: 0x%lx npages: 0x%lx\n"
			"  existing slot: %u paddr: 0x%lx size: 0x%lx",
			slot, guest_paddr, npages,
			region->region.slot,
			(uint64_t) region->region.guest_phys_addr,
			(uint64_t) region->region.memory_size);

	/* Allocate and initialize new mem region structure. */
	region = calloc(1, sizeof(*region));
	TEST_ASSERT(region != NULL, "Insufficient Memory");
	region->mmap_size = npages * vm->page_size;

#ifdef __s390x__
	/* On s390x, the host address must be aligned to 1M (due to PGSTEs) */
	alignment = 0x100000;
#else
	alignment = 1;
#endif

	if (src_type == VM_MEM_SRC_ANONYMOUS_THP)
		alignment = max(huge_page_size, alignment);

	/* Add enough memory to align up if necessary */
	if (alignment > 1)
		region->mmap_size += alignment;

	region->mmap_start = mmap(NULL, region->mmap_size,
				  PROT_READ | PROT_WRITE,
				  MAP_PRIVATE | MAP_ANONYMOUS
				  | (src_type == VM_MEM_SRC_ANONYMOUS_HUGETLB ? MAP_HUGETLB : 0),
				  -1, 0);
	TEST_ASSERT(region->mmap_start != MAP_FAILED,
		    "test_malloc failed, mmap_start: %p errno: %i",
		    region->mmap_start, errno);

	/* Align host address */
	region->host_mem = align(region->mmap_start, alignment);

	/* As needed perform madvise */
	if (src_type == VM_MEM_SRC_ANONYMOUS || src_type == VM_MEM_SRC_ANONYMOUS_THP) {
		ret = madvise(region->host_mem, npages * vm->page_size,
			     src_type == VM_MEM_SRC_ANONYMOUS ? MADV_NOHUGEPAGE : MADV_HUGEPAGE);
		TEST_ASSERT(ret == 0, "madvise failed,\n"
			    "  addr: %p\n"
			    "  length: 0x%lx\n"
			    "  src_type: %x",
			    region->host_mem, npages * vm->page_size, src_type);
	}

	region->unused_phy_pages = sparsebit_alloc();
	sparsebit_set_num(region->unused_phy_pages,
		guest_paddr >> vm->page_shift, npages);
	region->region.slot = slot;
	region->region.flags = flags;
	region->region.guest_phys_addr = guest_paddr;
	region->region.memory_size = npages * vm->page_size;
	region->region.userspace_addr = (uintptr_t) region->host_mem;
	ret = ioctl(vm->fd, KVM_SET_USER_MEMORY_REGION, &region->region);
	TEST_ASSERT(ret == 0, "KVM_SET_USER_MEMORY_REGION IOCTL failed,\n"
		"  rc: %i errno: %i\n"
		"  slot: %u flags: 0x%x\n"
		"  guest_phys_addr: 0x%lx size: 0x%lx",
		ret, errno, slot, flags,
		guest_paddr, (uint64_t) region->region.memory_size);

	/* Add to linked-list of memory regions. */
	if (vm->userspace_mem_region_head)
		vm->userspace_mem_region_head->prev = region;
	region->next = vm->userspace_mem_region_head;
	vm->userspace_mem_region_head = region;
}