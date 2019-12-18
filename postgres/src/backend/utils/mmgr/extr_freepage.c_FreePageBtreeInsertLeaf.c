#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int first_page; int npages; } ;
struct TYPE_8__ {scalar_t__ magic; int nused; } ;
struct TYPE_7__ {TYPE_4__* leaf_key; } ;
struct TYPE_9__ {TYPE_2__ hdr; TYPE_1__ u; } ;
typedef  int Size ;
typedef  int /*<<< orphan*/  FreePageBtreeLeafKey ;
typedef  TYPE_3__ FreePageBtree ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int FPM_ITEMS_PER_LEAF_PAGE ; 
 scalar_t__ FREE_PAGE_LEAF_MAGIC ; 
 int /*<<< orphan*/  memmove (TYPE_4__*,TYPE_4__*,int) ; 

__attribute__((used)) static void
FreePageBtreeInsertLeaf(FreePageBtree *btp, Size index, Size first_page,
						Size npages)
{
	Assert(btp->hdr.magic == FREE_PAGE_LEAF_MAGIC);
	Assert(btp->hdr.nused <= FPM_ITEMS_PER_LEAF_PAGE);
	Assert(index <= btp->hdr.nused);
	memmove(&btp->u.leaf_key[index + 1], &btp->u.leaf_key[index],
			sizeof(FreePageBtreeLeafKey) * (btp->hdr.nused - index));
	btp->u.leaf_key[index].first_page = first_page;
	btp->u.leaf_key[index].npages = npages;
	++btp->hdr.nused;
}