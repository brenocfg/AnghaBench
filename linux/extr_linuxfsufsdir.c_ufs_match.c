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
struct ufs_dir_entry {int /*<<< orphan*/  d_name; int /*<<< orphan*/  d_ino; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (unsigned char const*,int /*<<< orphan*/ ,int) ; 
 int ufs_get_de_namlen (struct super_block*,struct ufs_dir_entry*) ; 

__attribute__((used)) static inline int ufs_match(struct super_block *sb, int len,
		const unsigned char *name, struct ufs_dir_entry *de)
{
	if (len != ufs_get_de_namlen(sb, de))
		return 0;
	if (!de->d_ino)
		return 0;
	return !memcmp(name, de->d_name, len);
}