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
struct orangefs_bufmap {int page_count; int /*<<< orphan*/ * page_array; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
orangefs_bufmap_unmap(struct orangefs_bufmap *bufmap)
{
	int i;

	for (i = 0; i < bufmap->page_count; i++)
		put_page(bufmap->page_array[i]);
}