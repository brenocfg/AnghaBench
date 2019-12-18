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

/* Variables and functions */
 scalar_t__ ubifs_check_dir_empty (struct inode*) ; 

__attribute__((used)) static bool ubifs_crypt_empty_dir(struct inode *inode)
{
	return ubifs_check_dir_empty(inode) == 0;
}