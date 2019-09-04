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
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int nilfs_mdt_get_block (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct buffer_head**) ; 

__attribute__((used)) static inline int nilfs_sufile_get_header_block(struct inode *sufile,
						struct buffer_head **bhp)
{
	return nilfs_mdt_get_block(sufile, 0, 0, NULL, bhp);
}