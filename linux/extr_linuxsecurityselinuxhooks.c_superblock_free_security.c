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
struct superblock_security_struct {int dummy; } ;
struct super_block {struct superblock_security_struct* s_security; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct superblock_security_struct*) ; 

__attribute__((used)) static void superblock_free_security(struct super_block *sb)
{
	struct superblock_security_struct *sbsec = sb->s_security;
	sb->s_security = NULL;
	kfree(sbsec);
}