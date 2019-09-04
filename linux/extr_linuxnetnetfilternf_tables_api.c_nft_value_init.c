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
struct nlattr {int dummy; } ;
struct nft_data_desc {unsigned int len; int /*<<< orphan*/  type; } ;
struct nft_data {int /*<<< orphan*/  data; } ;
struct nft_ctx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  NFT_DATA_VALUE ; 
 unsigned int nla_len (struct nlattr const*) ; 
 int /*<<< orphan*/  nla_memcpy (int /*<<< orphan*/ ,struct nlattr const*,unsigned int) ; 

__attribute__((used)) static int nft_value_init(const struct nft_ctx *ctx,
			  struct nft_data *data, unsigned int size,
			  struct nft_data_desc *desc, const struct nlattr *nla)
{
	unsigned int len;

	len = nla_len(nla);
	if (len == 0)
		return -EINVAL;
	if (len > size)
		return -EOVERFLOW;

	nla_memcpy(data->data, nla, len);
	desc->type = NFT_DATA_VALUE;
	desc->len  = len;
	return 0;
}