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
struct tomoyo_page_dump {scalar_t__ data; struct page* page; } ;
struct page {int dummy; } ;
struct linux_binprm {struct page** page; int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOLL_FORCE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 unsigned long PAGE_SIZE ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ get_user_pages_remote (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ,struct page**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* kmap_atomic (struct page*) ; 
 int /*<<< orphan*/  kunmap_atomic (char*) ; 
 scalar_t__ kzalloc (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,unsigned long) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

bool tomoyo_dump_page(struct linux_binprm *bprm, unsigned long pos,
		      struct tomoyo_page_dump *dump)
{
	struct page *page;

	/* dump->data is released by tomoyo_find_next_domain(). */
	if (!dump->data) {
		dump->data = kzalloc(PAGE_SIZE, GFP_NOFS);
		if (!dump->data)
			return false;
	}
	/* Same with get_arg_page(bprm, pos, 0) in fs/exec.c */
#ifdef CONFIG_MMU
	/*
	 * This is called at execve() time in order to dig around
	 * in the argv/environment of the new proceess
	 * (represented by bprm).  'current' is the process doing
	 * the execve().
	 */
	if (get_user_pages_remote(current, bprm->mm, pos, 1,
				FOLL_FORCE, &page, NULL, NULL) <= 0)
		return false;
#else
	page = bprm->page[pos / PAGE_SIZE];
#endif
	if (page != dump->page) {
		const unsigned int offset = pos % PAGE_SIZE;
		/*
		 * Maybe kmap()/kunmap() should be used here.
		 * But remove_arg_zero() uses kmap_atomic()/kunmap_atomic().
		 * So do I.
		 */
		char *kaddr = kmap_atomic(page);

		dump->page = page;
		memcpy(dump->data + offset, kaddr + offset,
		       PAGE_SIZE - offset);
		kunmap_atomic(kaddr);
	}
	/* Same with put_arg_page(page) in fs/exec.c */
#ifdef CONFIG_MMU
	put_page(page);
#endif
	return true;
}