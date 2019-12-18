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
struct pcm512x_priv {int /*<<< orphan*/  pll_out; } ;

/* Variables and functions */
 unsigned long pcm512x_pll_max (struct pcm512x_priv*) ; 

__attribute__((used)) static unsigned long pcm512x_sck_max(struct pcm512x_priv *pcm512x)
{
	if (!pcm512x->pll_out)
		return 25000000;
	return pcm512x_pll_max(pcm512x);
}