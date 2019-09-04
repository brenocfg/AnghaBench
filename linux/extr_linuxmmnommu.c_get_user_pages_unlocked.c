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
struct page {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 long __get_user_pages_unlocked (TYPE_1__*,int /*<<< orphan*/ ,unsigned long,unsigned long,struct page**,unsigned int) ; 
 TYPE_1__* current ; 

long get_user_pages_unlocked(unsigned long start, unsigned long nr_pages,
			     struct page **pages, unsigned int gup_flags)
{
	return __get_user_pages_unlocked(current, current->mm, start, nr_pages,
					 pages, gup_flags);
}