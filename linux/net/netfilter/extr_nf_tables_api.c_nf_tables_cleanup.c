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
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFT_VALIDATE_SKIP ; 
 int /*<<< orphan*/  nft_validate_state_update (struct net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nf_tables_cleanup(struct net *net)
{
	nft_validate_state_update(net, NFT_VALIDATE_SKIP);
}