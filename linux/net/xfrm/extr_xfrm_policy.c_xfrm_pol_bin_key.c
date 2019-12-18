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
struct xfrm_pol_inexact_key {int type; int dir; int family; int /*<<< orphan*/  net; int /*<<< orphan*/  if_id; } ;

/* Variables and functions */
 int jhash_3words (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_hash_mix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_pnet (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 xfrm_pol_bin_key(const void *data, u32 len, u32 seed)
{
	const struct xfrm_pol_inexact_key *k = data;
	u32 a = k->type << 24 | k->dir << 16 | k->family;

	return jhash_3words(a, k->if_id, net_hash_mix(read_pnet(&k->net)),
			    seed);
}