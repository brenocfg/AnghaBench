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

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_DAIFMT_CBM_CFM ; 
 int lochnagar_sc_check_fmt (struct snd_soc_dai*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lochnagar_sc_set_usb_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	return lochnagar_sc_check_fmt(dai, fmt, SND_SOC_DAIFMT_CBM_CFM);
}