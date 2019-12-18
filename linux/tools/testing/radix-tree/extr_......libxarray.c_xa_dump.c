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
struct xarray {int /*<<< orphan*/  xa_flags; void* xa_head; } ;
struct TYPE_2__ {unsigned int shift; } ;

/* Variables and functions */
 unsigned int XA_CHUNK_SHIFT ; 
 int /*<<< orphan*/  XA_MARK_0 ; 
 int /*<<< orphan*/  XA_MARK_1 ; 
 int /*<<< orphan*/  XA_MARK_2 ; 
 int /*<<< orphan*/  pr_info (char*,struct xarray const*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_dump_entry (void*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ xa_is_node (void*) ; 
 int /*<<< orphan*/  xa_marked (struct xarray const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* xa_to_node (void*) ; 

void xa_dump(const struct xarray *xa)
{
	void *entry = xa->xa_head;
	unsigned int shift = 0;

	pr_info("xarray: %px head %px flags %x marks %d %d %d\n", xa, entry,
			xa->xa_flags, xa_marked(xa, XA_MARK_0),
			xa_marked(xa, XA_MARK_1), xa_marked(xa, XA_MARK_2));
	if (xa_is_node(entry))
		shift = xa_to_node(entry)->shift + XA_CHUNK_SHIFT;
	xa_dump_entry(entry, 0, shift);
}