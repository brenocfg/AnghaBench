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
#define  CLS_H_HIFI 130 
#define  CLS_H_LOHIFI 129 
#define  CLS_H_LP 128 
 int /*<<< orphan*/  wcd9335_codec_hph_hifi_config (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  wcd9335_codec_hph_lohifi_config (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  wcd9335_codec_hph_lp_config (struct snd_soc_component*,int) ; 

__attribute__((used)) static void wcd9335_codec_hph_mode_config(struct snd_soc_component *component,
					  int event, int mode)
{
	switch (mode) {
	case CLS_H_LP:
		wcd9335_codec_hph_lp_config(component, event);
		break;
	case CLS_H_LOHIFI:
		wcd9335_codec_hph_lohifi_config(component, event);
		break;
	case CLS_H_HIFI:
		wcd9335_codec_hph_hifi_config(component, event);
		break;
	}
}