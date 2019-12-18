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
struct swap_info_struct {int /*<<< orphan*/ * swap_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  Unused_offset ; 
 struct swap_info_struct* __swap_info_get (TYPE_1__) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t swp_offset (TYPE_1__) ; 

__attribute__((used)) static struct swap_info_struct *_swap_info_get(swp_entry_t entry)
{
	struct swap_info_struct *p;

	p = __swap_info_get(entry);
	if (!p)
		goto out;
	if (!p->swap_map[swp_offset(entry)])
		goto bad_free;
	return p;

bad_free:
	pr_err("swap_info_get: %s%08lx\n", Unused_offset, entry.val);
	goto out;
out:
	return NULL;
}