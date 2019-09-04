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
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {struct TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PG_SAFE ; 
 void* get_image_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* safe_pages_list ; 

__attribute__((used)) static void *__get_safe_page(gfp_t gfp_mask)
{
	if (safe_pages_list) {
		void *ret = safe_pages_list;

		safe_pages_list = safe_pages_list->next;
		memset(ret, 0, PAGE_SIZE);
		return ret;
	}
	return get_image_page(gfp_mask, PG_SAFE);
}