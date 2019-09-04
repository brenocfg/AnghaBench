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
struct nilfs_ifile_info {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 scalar_t__ NILFS_MDT (struct inode*) ; 

__attribute__((used)) static inline struct nilfs_ifile_info *NILFS_IFILE_I(struct inode *ifile)
{
	return (struct nilfs_ifile_info *)NILFS_MDT(ifile);
}