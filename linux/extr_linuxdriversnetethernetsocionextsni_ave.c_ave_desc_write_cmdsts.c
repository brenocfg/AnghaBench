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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
typedef  enum desc_id { ____Placeholder_desc_id } desc_id ;

/* Variables and functions */
 int /*<<< orphan*/  AVE_DESC_OFS_CMDSTS ; 
 int /*<<< orphan*/  ave_desc_write (struct net_device*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ave_desc_write_cmdsts(struct net_device *ndev, enum desc_id id,
				  int entry, u32 val)
{
	ave_desc_write(ndev, id, entry, AVE_DESC_OFS_CMDSTS, val);
}