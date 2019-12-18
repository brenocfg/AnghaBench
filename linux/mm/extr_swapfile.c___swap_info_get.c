#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ swp_entry_t ;
struct swap_info_struct {int flags; unsigned long max; } ;

/* Variables and functions */
 int /*<<< orphan*/  Bad_file ; 
 int /*<<< orphan*/  Bad_offset ; 
 int SWP_USED ; 
 int /*<<< orphan*/  Unused_file ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long swp_offset (TYPE_1__) ; 
 struct swap_info_struct* swp_swap_info (TYPE_1__) ; 

__attribute__((used)) static struct swap_info_struct *__swap_info_get(swp_entry_t entry)
{
	struct swap_info_struct *p;
	unsigned long offset;

	if (!entry.val)
		goto out;
	p = swp_swap_info(entry);
	if (!p)
		goto bad_nofile;
	if (!(p->flags & SWP_USED))
		goto bad_device;
	offset = swp_offset(entry);
	if (offset >= p->max)
		goto bad_offset;
	return p;

bad_offset:
	pr_err("swap_info_get: %s%08lx\n", Bad_offset, entry.val);
	goto out;
bad_device:
	pr_err("swap_info_get: %s%08lx\n", Unused_file, entry.val);
	goto out;
bad_nofile:
	pr_err("swap_info_get: %s%08lx\n", Bad_file, entry.val);
out:
	return NULL;
}