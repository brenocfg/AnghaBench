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
struct page_collect {int pg_first; TYPE_1__* sbi; TYPE_2__* inode; int /*<<< orphan*/  pages; struct ore_io_state* ios; int /*<<< orphan*/  length; } ;
struct ore_io_state {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; struct page_collect* private; int /*<<< orphan*/ * r4w; int /*<<< orphan*/  done; int /*<<< orphan*/  pages; } ;
struct exofs_i_info {int /*<<< orphan*/  oc; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_ino; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_curr_pending; int /*<<< orphan*/  layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct ore_io_state*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EXOFS_DBGMSG2 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXOFS_ERR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  _LLU (int /*<<< orphan*/ ) ; 
 int _maybe_not_all_in_one_io (struct ore_io_state*,struct page_collect*,struct page_collect*) ; 
 int /*<<< orphan*/  _pcol_reset (struct page_collect*) ; 
 int /*<<< orphan*/  _r4w_op ; 
 int /*<<< orphan*/  _unlock_pcol_pages (struct page_collect*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct exofs_i_info* exofs_i (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct page_collect*) ; 
 struct page_collect* kmalloc (int,int /*<<< orphan*/ ) ; 
 int ore_get_rw_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,struct ore_io_state**) ; 
 int ore_write (struct ore_io_state*) ; 
 int /*<<< orphan*/  pcol_free (struct page_collect*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writepages_done ; 

__attribute__((used)) static int write_exec(struct page_collect *pcol)
{
	struct exofs_i_info *oi = exofs_i(pcol->inode);
	struct ore_io_state *ios;
	struct page_collect *pcol_copy = NULL;
	int ret;

	if (!pcol->pages)
		return 0;

	BUG_ON(pcol->ios);
	ret = ore_get_rw_state(&pcol->sbi->layout, &oi->oc, false,
				 pcol->pg_first << PAGE_SHIFT,
				 pcol->length, &pcol->ios);
	if (unlikely(ret))
		goto err;

	pcol_copy = kmalloc(sizeof(*pcol_copy), GFP_KERNEL);
	if (!pcol_copy) {
		EXOFS_ERR("write_exec: Failed to kmalloc(pcol)\n");
		ret = -ENOMEM;
		goto err;
	}

	*pcol_copy = *pcol;

	ios = pcol->ios;
	ios->pages = pcol_copy->pages;
	ios->done = writepages_done;
	ios->r4w = &_r4w_op;
	ios->private = pcol_copy;

	/* pages ownership was passed to pcol_copy */
	_pcol_reset(pcol);

	ret = _maybe_not_all_in_one_io(ios, pcol_copy, pcol);
	if (unlikely(ret))
		goto err;

	EXOFS_DBGMSG2("write_exec(0x%lx) offset=0x%llx length=0x%llx\n",
		pcol->inode->i_ino, _LLU(ios->offset), _LLU(ios->length));

	ret = ore_write(ios);
	if (unlikely(ret)) {
		EXOFS_ERR("write_exec: ore_write() Failed\n");
		goto err;
	}

	atomic_inc(&pcol->sbi->s_curr_pending);
	return 0;

err:
	if (!pcol_copy) /* Failed before ownership transfer */
		pcol_copy = pcol;
	_unlock_pcol_pages(pcol_copy, ret, WRITE);
	pcol_free(pcol_copy);
	kfree(pcol_copy);

	return ret;
}