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
struct z_erofs_vle_work_builder {scalar_t__ role; TYPE_1__* work; int /*<<< orphan*/  vector; } ;
struct page {int dummy; } ;
typedef  enum z_erofs_page_type { ____Placeholder_z_erofs_page_type } z_erofs_page_type ;
struct TYPE_2__ {int /*<<< orphan*/  vcnt; } ;

/* Variables and functions */
 int EAGAIN ; 
 int Z_EROFS_PAGE_TYPE_EXCLUSIVE ; 
 scalar_t__ Z_EROFS_VLE_WORK_PRIMARY ; 
 scalar_t__ try_to_reuse_as_compressed_page (struct z_erofs_vle_work_builder*,struct page*) ; 
 int z_erofs_pagevec_ctor_enqueue (int /*<<< orphan*/ *,struct page*,int,int*) ; 

__attribute__((used)) static int z_erofs_vle_work_add_page(
	struct z_erofs_vle_work_builder *builder,
	struct page *page,
	enum z_erofs_page_type type)
{
	int ret;
	bool occupied;

	/* give priority for the compressed data storage */
	if (builder->role >= Z_EROFS_VLE_WORK_PRIMARY &&
		type == Z_EROFS_PAGE_TYPE_EXCLUSIVE &&
		try_to_reuse_as_compressed_page(builder, page))
		return 0;

	ret = z_erofs_pagevec_ctor_enqueue(&builder->vector,
		page, type, &occupied);
	builder->work->vcnt += (unsigned)ret;

	return ret ? 0 : -EAGAIN;
}