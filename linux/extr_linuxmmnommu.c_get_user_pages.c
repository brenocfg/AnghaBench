#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 long __get_user_pages (TYPE_1__*,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned int,struct page**,struct vm_area_struct**,int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 

long get_user_pages(unsigned long start, unsigned long nr_pages,
		    unsigned int gup_flags, struct page **pages,
		    struct vm_area_struct **vmas)
{
	return __get_user_pages(current, current->mm, start, nr_pages,
				gup_flags, pages, vmas, NULL);
}