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
struct idr {scalar_t__ idr_base; int /*<<< orphan*/  idr_rt; } ;

/* Variables and functions */
 void* radix_tree_delete_item (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

void *idr_remove(struct idr *idr, unsigned long id)
{
	return radix_tree_delete_item(&idr->idr_rt, id - idr->idr_base, NULL);
}