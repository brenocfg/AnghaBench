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
struct nft_counter_percpu_priv {int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nft_counter_do_destroy(struct nft_counter_percpu_priv *priv)
{
	free_percpu(priv->counter);
}