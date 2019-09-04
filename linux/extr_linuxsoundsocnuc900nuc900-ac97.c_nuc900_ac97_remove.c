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
struct snd_soc_dai {int dummy; } ;
struct nuc900_audio {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct nuc900_audio* nuc900_ac97_data ; 

__attribute__((used)) static int nuc900_ac97_remove(struct snd_soc_dai *dai)
{
	struct nuc900_audio *nuc900_audio = nuc900_ac97_data;

	clk_disable(nuc900_audio->clk);
	return 0;
}