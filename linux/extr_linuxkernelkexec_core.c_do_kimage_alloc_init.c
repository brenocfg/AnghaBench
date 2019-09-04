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
struct kimage {int /*<<< orphan*/  unusable_pages; int /*<<< orphan*/  dest_pages; int /*<<< orphan*/  control_pages; int /*<<< orphan*/  type; int /*<<< orphan*/  control_page; scalar_t__ head; scalar_t__* last_entry; scalar_t__* entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEXEC_TYPE_DEFAULT ; 
 struct kimage* kzalloc (int,int /*<<< orphan*/ ) ; 

struct kimage *do_kimage_alloc_init(void)
{
	struct kimage *image;

	/* Allocate a controlling structure */
	image = kzalloc(sizeof(*image), GFP_KERNEL);
	if (!image)
		return NULL;

	image->head = 0;
	image->entry = &image->head;
	image->last_entry = &image->head;
	image->control_page = ~0; /* By default this does not apply */
	image->type = KEXEC_TYPE_DEFAULT;

	/* Initialize the list of control pages */
	INIT_LIST_HEAD(&image->control_pages);

	/* Initialize the list of destination pages */
	INIT_LIST_HEAD(&image->dest_pages);

	/* Initialize the list of unusable pages */
	INIT_LIST_HEAD(&image->unusable_pages);

	return image;
}