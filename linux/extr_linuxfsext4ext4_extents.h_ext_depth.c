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
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  eh_depth; } ;

/* Variables and functions */
 TYPE_1__* ext_inode_hdr (struct inode*) ; 
 unsigned short le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned short ext_depth(struct inode *inode)
{
	return le16_to_cpu(ext_inode_hdr(inode)->eh_depth);
}