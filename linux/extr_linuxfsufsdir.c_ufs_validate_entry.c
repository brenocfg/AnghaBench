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
struct ufs_dir_entry {int dummy; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 struct ufs_dir_entry* ufs_next_entry (struct super_block*,struct ufs_dir_entry*) ; 

__attribute__((used)) static inline unsigned
ufs_validate_entry(struct super_block *sb, char *base,
		   unsigned offset, unsigned mask)
{
	struct ufs_dir_entry *de = (struct ufs_dir_entry*)(base + offset);
	struct ufs_dir_entry *p = (struct ufs_dir_entry*)(base + (offset&mask));
	while ((char*)p < (char*)de)
		p = ufs_next_entry(sb, p);
	return (char *)p - base;
}