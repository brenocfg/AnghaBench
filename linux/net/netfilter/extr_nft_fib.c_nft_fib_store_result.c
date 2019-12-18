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
typedef  int u32 ;
struct nft_fib {int result; int flags; } ;
struct net_device {int ifindex; char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int NFTA_FIB_F_PRESENT ; 
#define  NFT_FIB_RESULT_OIF 129 
#define  NFT_FIB_RESULT_OIFNAME 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  strncpy (void*,char*,int /*<<< orphan*/ ) ; 

void nft_fib_store_result(void *reg, const struct nft_fib *priv,
			  const struct net_device *dev)
{
	u32 *dreg = reg;
	int index;

	switch (priv->result) {
	case NFT_FIB_RESULT_OIF:
		index = dev ? dev->ifindex : 0;
		*dreg = (priv->flags & NFTA_FIB_F_PRESENT) ? !!index : index;
		break;
	case NFT_FIB_RESULT_OIFNAME:
		if (priv->flags & NFTA_FIB_F_PRESENT)
			*dreg = !!dev;
		else
			strncpy(reg, dev ? dev->name : "", IFNAMSIZ);
		break;
	default:
		WARN_ON_ONCE(1);
		*dreg = 0;
		break;
	}
}