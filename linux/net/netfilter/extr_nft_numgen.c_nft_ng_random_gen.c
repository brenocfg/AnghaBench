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
typedef  scalar_t__ u32 ;
struct rnd_state {int dummy; } ;
struct nft_ng_random {scalar_t__ offset; int /*<<< orphan*/  modulus; } ;

/* Variables and functions */
 int /*<<< orphan*/  nft_numgen_prandom_state ; 
 int /*<<< orphan*/  prandom_u32_state (struct rnd_state*) ; 
 scalar_t__ reciprocal_scale (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rnd_state* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 nft_ng_random_gen(struct nft_ng_random *priv)
{
	struct rnd_state *state = this_cpu_ptr(&nft_numgen_prandom_state);

	return reciprocal_scale(prandom_u32_state(state), priv->modulus) +
	       priv->offset;
}