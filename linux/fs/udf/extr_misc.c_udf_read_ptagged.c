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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct super_block {int dummy; } ;
struct kernel_lb_addr {scalar_t__ logicalBlockNum; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  udf_get_lb_pblock (struct super_block*,struct kernel_lb_addr*,scalar_t__) ; 
 struct buffer_head* udf_read_tagged (struct super_block*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

struct buffer_head *udf_read_ptagged(struct super_block *sb,
				     struct kernel_lb_addr *loc,
				     uint32_t offset, uint16_t *ident)
{
	return udf_read_tagged(sb, udf_get_lb_pblock(sb, loc, offset),
			       loc->logicalBlockNum + offset, ident);
}