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
struct to_kill {int dummy; } ;
struct page {int /*<<< orphan*/  mapping; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  collect_procs_anon (struct page*,struct list_head*,struct to_kill**,int) ; 
 int /*<<< orphan*/  collect_procs_file (struct page*,struct list_head*,struct to_kill**,int) ; 
 int /*<<< orphan*/  kfree (struct to_kill*) ; 
 struct to_kill* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void collect_procs(struct page *page, struct list_head *tokill,
				int force_early)
{
	struct to_kill *tk;

	if (!page->mapping)
		return;

	tk = kmalloc(sizeof(struct to_kill), GFP_NOIO);
	if (!tk)
		return;
	if (PageAnon(page))
		collect_procs_anon(page, tokill, &tk, force_early);
	else
		collect_procs_file(page, tokill, &tk, force_early);
	kfree(tk);
}