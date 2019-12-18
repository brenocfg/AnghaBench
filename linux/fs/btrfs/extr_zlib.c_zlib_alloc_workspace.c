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
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  workspace; } ;
struct workspace {unsigned int level; struct list_head list; int /*<<< orphan*/  buf; TYPE_1__ strm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct list_head* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  MAX_MEM_LEVEL ; 
 int /*<<< orphan*/  MAX_WBITS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmalloc (int,int /*<<< orphan*/ ) ; 
 struct workspace* kzalloc (int,int /*<<< orphan*/ ) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_deflate_workspacesize (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlib_free_workspace (struct list_head*) ; 
 int /*<<< orphan*/  zlib_inflate_workspacesize () ; 

__attribute__((used)) static struct list_head *zlib_alloc_workspace(unsigned int level)
{
	struct workspace *workspace;
	int workspacesize;

	workspace = kzalloc(sizeof(*workspace), GFP_KERNEL);
	if (!workspace)
		return ERR_PTR(-ENOMEM);

	workspacesize = max(zlib_deflate_workspacesize(MAX_WBITS, MAX_MEM_LEVEL),
			zlib_inflate_workspacesize());
	workspace->strm.workspace = kvmalloc(workspacesize, GFP_KERNEL);
	workspace->level = level;
	workspace->buf = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (!workspace->strm.workspace || !workspace->buf)
		goto fail;

	INIT_LIST_HEAD(&workspace->list);

	return &workspace->list;
fail:
	zlib_free_workspace(&workspace->list);
	return ERR_PTR(-ENOMEM);
}