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
struct nft_data {int dummy; } ;
typedef  enum nft_data_types { ____Placeholder_nft_data_types } nft_data_types ;

/* Variables and functions */
#define  NFT_DATA_VERDICT 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 void nft_verdict_uninit (struct nft_data const*) ; 

void nft_data_release(const struct nft_data *data, enum nft_data_types type)
{
	if (type < NFT_DATA_VERDICT)
		return;
	switch (type) {
	case NFT_DATA_VERDICT:
		return nft_verdict_uninit(data);
	default:
		WARN_ON(1);
	}
}