#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct xdp_umem_reg {scalar_t__ chunk_size; scalar_t__ headroom; scalar_t__ addr; scalar_t__ len; } ;
struct TYPE_3__ {scalar_t__ size; scalar_t__ chunk_mask; } ;
struct xdp_umem {unsigned long address; int npgs; int /*<<< orphan*/  pid; int /*<<< orphan*/ * pgs; TYPE_2__* pages; int /*<<< orphan*/  users; int /*<<< orphan*/  xsk_list_lock; int /*<<< orphan*/  xsk_list; int /*<<< orphan*/ * user; scalar_t__ chunk_size_nohr; scalar_t__ headroom; TYPE_1__ props; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ ALIGN (scalar_t__,int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PAGE_ALIGNED (scalar_t__) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int XDP_PACKET_HEADROOM ; 
 scalar_t__ XDP_UMEM_MIN_CHUNK_SIZE ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ div_u64 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  get_task_pid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_power_of_2 (scalar_t__) ; 
 TYPE_2__* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int xdp_umem_account_pages (struct xdp_umem*) ; 
 int xdp_umem_pin_pages (struct xdp_umem*) ; 
 int /*<<< orphan*/  xdp_umem_unaccount_pages (struct xdp_umem*) ; 

__attribute__((used)) static int xdp_umem_reg(struct xdp_umem *umem, struct xdp_umem_reg *mr)
{
	u32 chunk_size = mr->chunk_size, headroom = mr->headroom;
	unsigned int chunks, chunks_per_page;
	u64 addr = mr->addr, size = mr->len;
	int size_chk, err, i;

	if (chunk_size < XDP_UMEM_MIN_CHUNK_SIZE || chunk_size > PAGE_SIZE) {
		/* Strictly speaking we could support this, if:
		 * - huge pages, or*
		 * - using an IOMMU, or
		 * - making sure the memory area is consecutive
		 * but for now, we simply say "computer says no".
		 */
		return -EINVAL;
	}

	if (!is_power_of_2(chunk_size))
		return -EINVAL;

	if (!PAGE_ALIGNED(addr)) {
		/* Memory area has to be page size aligned. For
		 * simplicity, this might change.
		 */
		return -EINVAL;
	}

	if ((addr + size) < addr)
		return -EINVAL;

	chunks = (unsigned int)div_u64(size, chunk_size);
	if (chunks == 0)
		return -EINVAL;

	chunks_per_page = PAGE_SIZE / chunk_size;
	if (chunks < chunks_per_page || chunks % chunks_per_page)
		return -EINVAL;

	headroom = ALIGN(headroom, 64);

	size_chk = chunk_size - headroom - XDP_PACKET_HEADROOM;
	if (size_chk < 0)
		return -EINVAL;

	umem->pid = get_task_pid(current, PIDTYPE_PID);
	umem->address = (unsigned long)addr;
	umem->props.chunk_mask = ~((u64)chunk_size - 1);
	umem->props.size = size;
	umem->headroom = headroom;
	umem->chunk_size_nohr = chunk_size - headroom;
	umem->npgs = size / PAGE_SIZE;
	umem->pgs = NULL;
	umem->user = NULL;
	INIT_LIST_HEAD(&umem->xsk_list);
	spin_lock_init(&umem->xsk_list_lock);

	refcount_set(&umem->users, 1);

	err = xdp_umem_account_pages(umem);
	if (err)
		goto out;

	err = xdp_umem_pin_pages(umem);
	if (err)
		goto out_account;

	umem->pages = kcalloc(umem->npgs, sizeof(*umem->pages), GFP_KERNEL);
	if (!umem->pages) {
		err = -ENOMEM;
		goto out_account;
	}

	for (i = 0; i < umem->npgs; i++)
		umem->pages[i].addr = page_address(umem->pgs[i]);

	return 0;

out_account:
	xdp_umem_unaccount_pages(umem);
out:
	put_pid(umem->pid);
	return err;
}