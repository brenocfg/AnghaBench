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
struct address_space {int /*<<< orphan*/  i_pages; } ;

/* Variables and functions */
 int radix_tree_tagged (int /*<<< orphan*/ *,int) ; 

int mapping_tagged(struct address_space *mapping, int tag)
{
	return radix_tree_tagged(&mapping->i_pages, tag);
}