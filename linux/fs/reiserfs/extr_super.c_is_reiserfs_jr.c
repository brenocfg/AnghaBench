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
struct TYPE_2__ {int /*<<< orphan*/  s_magic; } ;
struct reiserfs_super_block {TYPE_1__ s_v1; } ;

/* Variables and functions */
 int /*<<< orphan*/  reiserfs_jr_magic_string ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int is_reiserfs_jr(struct reiserfs_super_block *rs)
{
	return !strncmp(rs->s_v1.s_magic, reiserfs_jr_magic_string,
			strlen(reiserfs_jr_magic_string));
}