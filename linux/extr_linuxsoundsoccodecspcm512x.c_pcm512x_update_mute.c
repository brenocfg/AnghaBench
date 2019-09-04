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
struct pcm512x_priv {int mute; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCM512x_MUTE ; 
 int PCM512x_RQML ; 
 int PCM512x_RQML_SHIFT ; 
 int PCM512x_RQMR ; 
 int PCM512x_RQMR_SHIFT ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int pcm512x_update_mute(struct pcm512x_priv *pcm512x)
{
	return regmap_update_bits(
		pcm512x->regmap, PCM512x_MUTE, PCM512x_RQML | PCM512x_RQMR,
		(!!(pcm512x->mute & 0x5) << PCM512x_RQML_SHIFT)
		| (!!(pcm512x->mute & 0x3) << PCM512x_RQMR_SHIFT));
}