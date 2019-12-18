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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int simtec_audio_core_probe (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_machine_simtec_aic23 ; 

__attribute__((used)) static int simtec_audio_tlv320aic23_probe(struct platform_device *pd)
{
	return simtec_audio_core_probe(pd, &snd_soc_machine_simtec_aic23);
}