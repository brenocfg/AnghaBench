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
 int EINVAL ; 
#define  RT5640_AIF1 137 
#define  RT5640_AIF2 136 
 int /*<<< orphan*/  RT5640_I2S1_SDP ; 
 int RT5640_I2S_IF_MASK ; 
 int RT5640_I2S_IF_SFT ; 
#define  RT5640_IF_113 135 
#define  RT5640_IF_123 134 
#define  RT5640_IF_132 133 
#define  RT5640_IF_213 132 
#define  RT5640_IF_223 131 
#define  RT5640_IF_231 130 
#define  RT5640_IF_312 129 
#define  RT5640_IF_321 128 
 int RT5640_U_IF1 ; 
 int RT5640_U_IF2 ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_sdp_info(struct snd_soc_component *component, int dai_id)
{
	int ret = 0, val;

	if (component == NULL)
		return -EINVAL;

	val = snd_soc_component_read32(component, RT5640_I2S1_SDP);
	val = (val & RT5640_I2S_IF_MASK) >> RT5640_I2S_IF_SFT;
	switch (dai_id) {
	case RT5640_AIF1:
		switch (val) {
		case RT5640_IF_123:
		case RT5640_IF_132:
			ret |= RT5640_U_IF1;
			break;
		case RT5640_IF_113:
			ret |= RT5640_U_IF1;
			/* fall through */
		case RT5640_IF_312:
		case RT5640_IF_213:
			ret |= RT5640_U_IF2;
			break;
		}
		break;

	case RT5640_AIF2:
		switch (val) {
		case RT5640_IF_231:
		case RT5640_IF_213:
			ret |= RT5640_U_IF1;
			break;
		case RT5640_IF_223:
			ret |= RT5640_U_IF1;
			/* fall through */
		case RT5640_IF_123:
		case RT5640_IF_321:
			ret |= RT5640_U_IF2;
			break;
		}
		break;

	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}