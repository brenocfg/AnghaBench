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
struct snd_soc_component {int dummy; } ;
struct nau8825 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nau8825_xtalk_cancel (struct nau8825*) ; 
 struct nau8825* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static void nau8825_component_remove(struct snd_soc_component *component)
{
	struct nau8825 *nau8825 = snd_soc_component_get_drvdata(component);

	/* Cancel and reset cross tak suppresstion detection funciton */
	nau8825_xtalk_cancel(nau8825);
}