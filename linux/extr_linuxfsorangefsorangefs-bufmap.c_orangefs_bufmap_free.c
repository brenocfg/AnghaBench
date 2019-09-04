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
struct orangefs_bufmap {struct orangefs_bufmap* buffer_index_array; struct orangefs_bufmap* desc_array; struct orangefs_bufmap* page_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct orangefs_bufmap*) ; 

__attribute__((used)) static void
orangefs_bufmap_free(struct orangefs_bufmap *bufmap)
{
	kfree(bufmap->page_array);
	kfree(bufmap->desc_array);
	kfree(bufmap->buffer_index_array);
	kfree(bufmap);
}