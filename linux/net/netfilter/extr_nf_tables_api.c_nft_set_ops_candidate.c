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
struct nft_set_type {int features; } ;

/* Variables and functions */
 int NFT_SET_FEATURES ; 

__attribute__((used)) static bool nft_set_ops_candidate(const struct nft_set_type *type, u32 flags)
{
	return (flags & type->features) == (flags & NFT_SET_FEATURES);
}