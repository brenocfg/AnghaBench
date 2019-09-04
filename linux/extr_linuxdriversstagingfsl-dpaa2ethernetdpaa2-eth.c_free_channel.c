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
struct dpaa2_eth_priv {int dummy; } ;
struct dpaa2_eth_channel {int /*<<< orphan*/  dpcon; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_dpcon (struct dpaa2_eth_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dpaa2_eth_channel*) ; 

__attribute__((used)) static void free_channel(struct dpaa2_eth_priv *priv,
			 struct dpaa2_eth_channel *channel)
{
	free_dpcon(priv, channel->dpcon);
	kfree(channel);
}