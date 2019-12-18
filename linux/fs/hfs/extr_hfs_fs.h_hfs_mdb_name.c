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
struct super_block {char const* s_id; } ;

/* Variables and functions */

__attribute__((used)) static inline const char *hfs_mdb_name(struct super_block *sb)
{
	return sb->s_id;
}