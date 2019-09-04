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
struct TYPE_3__ {int /*<<< orphan*/ * refs; } ;
struct TYPE_4__ {TYPE_1__ imp; } ;
struct gntdev_dmabuf {int nr_pages; TYPE_2__ u; void* pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct gntdev_dmabuf* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GRANT_INVALID_REF ; 
 int /*<<< orphan*/  dmabuf_imp_free_storage (struct gntdev_dmabuf*) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct gntdev_dmabuf* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct gntdev_dmabuf *dmabuf_imp_alloc_storage(int count)
{
	struct gntdev_dmabuf *gntdev_dmabuf;
	int i;

	gntdev_dmabuf = kzalloc(sizeof(*gntdev_dmabuf), GFP_KERNEL);
	if (!gntdev_dmabuf)
		goto fail_no_free;

	gntdev_dmabuf->u.imp.refs = kcalloc(count,
					    sizeof(gntdev_dmabuf->u.imp.refs[0]),
					    GFP_KERNEL);
	if (!gntdev_dmabuf->u.imp.refs)
		goto fail;

	gntdev_dmabuf->pages = kcalloc(count,
				       sizeof(gntdev_dmabuf->pages[0]),
				       GFP_KERNEL);
	if (!gntdev_dmabuf->pages)
		goto fail;

	gntdev_dmabuf->nr_pages = count;

	for (i = 0; i < count; i++)
		gntdev_dmabuf->u.imp.refs[i] = GRANT_INVALID_REF;

	return gntdev_dmabuf;

fail:
	dmabuf_imp_free_storage(gntdev_dmabuf);
fail_no_free:
	return ERR_PTR(-ENOMEM);
}