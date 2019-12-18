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
struct reiserfs_security_handle {int dummy; } ;
struct qstr {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int reiserfs_security_init(struct inode *dir,
					 struct inode *inode,
					 const struct qstr *qstr,
					 struct reiserfs_security_handle *sec)
{
	return 0;
}