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
struct net_device {int dummy; } ;
struct ave_private {int dummy; } ;
typedef  enum desc_id { ____Placeholder_desc_id } desc_id ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVE_DESC_OFS_ADDRL ; 
 int /*<<< orphan*/  AVE_DESC_OFS_ADDRU ; 
 scalar_t__ IS_DESC_64BIT (struct ave_private*) ; 
 int /*<<< orphan*/  ave_desc_write (struct net_device*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ave_desc_write_addr(struct net_device *ndev, enum desc_id id,
				int entry, dma_addr_t paddr)
{
	struct ave_private *priv = netdev_priv(ndev);

	ave_desc_write(ndev, id, entry, AVE_DESC_OFS_ADDRL,
		       lower_32_bits(paddr));
	if (IS_DESC_64BIT(priv))
		ave_desc_write(ndev, id,
			       entry, AVE_DESC_OFS_ADDRU,
			       upper_32_bits(paddr));
}