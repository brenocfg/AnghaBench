#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {size_t relptr_off; } ;
struct TYPE_14__ {TYPE_3__* internal_key; TYPE_1__* leaf_key; } ;
struct TYPE_12__ {scalar_t__ magic; size_t nused; TYPE_7__ parent; } ;
struct TYPE_15__ {TYPE_4__ u; TYPE_2__ hdr; } ;
struct TYPE_13__ {size_t first_page; TYPE_7__ child; } ;
struct TYPE_11__ {size_t first_page; size_t npages; } ;
typedef  int /*<<< orphan*/  StringInfo ;
typedef  size_t Size ;
typedef  int /*<<< orphan*/  FreePageManager ;
typedef  TYPE_5__ FreePageBtree ;

/* Variables and functions */
 size_t FPM_PAGE_SIZE ; 
 scalar_t__ FREE_PAGE_INTERNAL_MAGIC ; 
 int /*<<< orphan*/  appendStringInfo (int /*<<< orphan*/ ,char*,size_t,size_t,...) ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 size_t fpm_pointer_to_page (char*,TYPE_5__*) ; 
 char* fpm_segment_base (int /*<<< orphan*/ *) ; 
 TYPE_5__* relptr_access (char*,TYPE_7__) ; 

__attribute__((used)) static void
FreePageManagerDumpBtree(FreePageManager *fpm, FreePageBtree *btp,
						 FreePageBtree *parent, int level, StringInfo buf)
{
	char	   *base = fpm_segment_base(fpm);
	Size		pageno = fpm_pointer_to_page(base, btp);
	Size		index;
	FreePageBtree *check_parent;

	check_stack_depth();
	check_parent = relptr_access(base, btp->hdr.parent);
	appendStringInfo(buf, "  %zu@%d %c", pageno, level,
					 btp->hdr.magic == FREE_PAGE_INTERNAL_MAGIC ? 'i' : 'l');
	if (parent != check_parent)
		appendStringInfo(buf, " [actual parent %zu, expected %zu]",
						 fpm_pointer_to_page(base, check_parent),
						 fpm_pointer_to_page(base, parent));
	appendStringInfoChar(buf, ':');
	for (index = 0; index < btp->hdr.nused; ++index)
	{
		if (btp->hdr.magic == FREE_PAGE_INTERNAL_MAGIC)
			appendStringInfo(buf, " %zu->%zu",
							 btp->u.internal_key[index].first_page,
							 btp->u.internal_key[index].child.relptr_off / FPM_PAGE_SIZE);
		else
			appendStringInfo(buf, " %zu(%zu)",
							 btp->u.leaf_key[index].first_page,
							 btp->u.leaf_key[index].npages);
	}
	appendStringInfoChar(buf, '\n');

	if (btp->hdr.magic == FREE_PAGE_INTERNAL_MAGIC)
	{
		for (index = 0; index < btp->hdr.nused; ++index)
		{
			FreePageBtree *child;

			child = relptr_access(base, btp->u.internal_key[index].child);
			FreePageManagerDumpBtree(fpm, child, btp, level + 1, buf);
		}
	}
}