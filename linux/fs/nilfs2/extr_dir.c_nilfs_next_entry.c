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
struct nilfs_dir_entry {int /*<<< orphan*/  rec_len; } ;

/* Variables and functions */
 int nilfs_rec_len_from_disk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nilfs_dir_entry *nilfs_next_entry(struct nilfs_dir_entry *p)
{
	return (struct nilfs_dir_entry *)((char *)p +
					  nilfs_rec_len_from_disk(p->rec_len));
}