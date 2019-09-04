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
struct inode {int dummy; } ;
struct extent_status {scalar_t__ es_len; scalar_t__ es_lblk; } ;
typedef  scalar_t__ ext4_lblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_es_find_delayed_extent_range (struct inode*,scalar_t__,scalar_t__,struct extent_status*) ; 

int ext4_find_delalloc_range(struct inode *inode,
			     ext4_lblk_t lblk_start,
			     ext4_lblk_t lblk_end)
{
	struct extent_status es;

	ext4_es_find_delayed_extent_range(inode, lblk_start, lblk_end, &es);
	if (es.es_len == 0)
		return 0; /* there is no delay extent in this tree */
	else if (es.es_lblk <= lblk_start &&
		 lblk_start < es.es_lblk + es.es_len)
		return 1;
	else if (lblk_start <= es.es_lblk && es.es_lblk <= lblk_end)
		return 1;
	else
		return 0;
}