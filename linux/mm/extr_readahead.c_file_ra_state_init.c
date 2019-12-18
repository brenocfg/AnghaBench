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
struct file_ra_state {int prev_pos; int /*<<< orphan*/  ra_pages; } ;
struct address_space {int /*<<< orphan*/  host; } ;
struct TYPE_2__ {int /*<<< orphan*/  ra_pages; } ;

/* Variables and functions */
 TYPE_1__* inode_to_bdi (int /*<<< orphan*/ ) ; 

void
file_ra_state_init(struct file_ra_state *ra, struct address_space *mapping)
{
	ra->ra_pages = inode_to_bdi(mapping->host)->ra_pages;
	ra->prev_pos = -1;
}