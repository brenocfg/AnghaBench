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
struct nft_ng_inc {scalar_t__ modulus; scalar_t__ offset; int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 scalar_t__ atomic_cmpxchg (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 nft_ng_inc_gen(struct nft_ng_inc *priv)
{
	u32 nval, oval;

	do {
		oval = atomic_read(&priv->counter);
		nval = (oval + 1 < priv->modulus) ? oval + 1 : 0;
	} while (atomic_cmpxchg(&priv->counter, oval, nval) != oval);

	return nval + priv->offset;
}