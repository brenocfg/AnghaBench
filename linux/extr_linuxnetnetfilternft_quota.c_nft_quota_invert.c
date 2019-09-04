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
struct nft_quota {int flags; } ;

/* Variables and functions */
 int NFT_QUOTA_F_INV ; 

__attribute__((used)) static inline bool nft_quota_invert(struct nft_quota *priv)
{
	return priv->flags & NFT_QUOTA_F_INV;
}