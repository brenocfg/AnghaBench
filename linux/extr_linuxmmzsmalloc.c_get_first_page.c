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
struct zspage {struct page* first_page; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  is_first_page (struct page*) ; 

__attribute__((used)) static inline struct page *get_first_page(struct zspage *zspage)
{
	struct page *first_page = zspage->first_page;

	VM_BUG_ON_PAGE(!is_first_page(first_page), first_page);
	return first_page;
}