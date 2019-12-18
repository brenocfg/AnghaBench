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

/* Variables and functions */
 int /*<<< orphan*/  snd_soc_component_set_drvdata (struct snd_soc_component*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txx9aclc_soc_device ; 

__attribute__((used)) static int txx9aclc_pcm_probe(struct snd_soc_component *component)
{
	snd_soc_component_set_drvdata(component, &txx9aclc_soc_device);
	return 0;
}