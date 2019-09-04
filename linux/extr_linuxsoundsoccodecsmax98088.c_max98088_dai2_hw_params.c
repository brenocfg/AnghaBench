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
typedef  int /*<<< orphan*/  u8 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct max98088_priv {scalar_t__ sysclk; struct max98088_cdata* dai; } ;
struct max98088_cdata {unsigned int rate; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  M98088_CLKMODE_MASK ; 
 int /*<<< orphan*/  M98088_DAI_DHF ; 
 int M98088_DAI_MAS ; 
 int /*<<< orphan*/  M98088_DAI_WS ; 
 int /*<<< orphan*/  M98088_REG_19_DAI2_CLKMODE ; 
 int /*<<< orphan*/  M98088_REG_1A_DAI2_CLKCFG_HI ; 
 int /*<<< orphan*/  M98088_REG_1B_DAI2_CLKCFG_LO ; 
 int /*<<< orphan*/  M98088_REG_1C_DAI2_FORMAT ; 
 int /*<<< orphan*/  M98088_REG_20_DAI2_FILTERS ; 
 int /*<<< orphan*/  M98088_REG_51_PWR_SYS ; 
 int /*<<< orphan*/  M98088_SHDNRUN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long long) ; 
 unsigned int params_rate (struct snd_pcm_hw_params*) ; 
 int params_width (struct snd_pcm_hw_params*) ; 
 scalar_t__ rate_value (unsigned int,int /*<<< orphan*/ *) ; 
 struct max98088_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static int max98088_dai2_hw_params(struct snd_pcm_substream *substream,
                                  struct snd_pcm_hw_params *params,
                                  struct snd_soc_dai *dai)
{
       struct snd_soc_component *component = dai->component;
       struct max98088_priv *max98088 = snd_soc_component_get_drvdata(component);
       struct max98088_cdata *cdata;
       unsigned long long ni;
       unsigned int rate;
       u8 regval;

       cdata = &max98088->dai[1];

       rate = params_rate(params);

       switch (params_width(params)) {
       case 16:
               snd_soc_component_update_bits(component, M98088_REG_1C_DAI2_FORMAT,
                       M98088_DAI_WS, 0);
               break;
       case 24:
               snd_soc_component_update_bits(component, M98088_REG_1C_DAI2_FORMAT,
                       M98088_DAI_WS, M98088_DAI_WS);
               break;
       default:
               return -EINVAL;
       }

       snd_soc_component_update_bits(component, M98088_REG_51_PWR_SYS, M98088_SHDNRUN, 0);

       if (rate_value(rate, &regval))
               return -EINVAL;

       snd_soc_component_update_bits(component, M98088_REG_19_DAI2_CLKMODE,
               M98088_CLKMODE_MASK, regval);
       cdata->rate = rate;

       /* Configure NI when operating as master */
       if (snd_soc_component_read32(component, M98088_REG_1C_DAI2_FORMAT)
               & M98088_DAI_MAS) {
               if (max98088->sysclk == 0) {
                       dev_err(component->dev, "Invalid system clock frequency\n");
                       return -EINVAL;
               }
               ni = 65536ULL * (rate < 50000 ? 96ULL : 48ULL)
                               * (unsigned long long int)rate;
               do_div(ni, (unsigned long long int)max98088->sysclk);
               snd_soc_component_write(component, M98088_REG_1A_DAI2_CLKCFG_HI,
                       (ni >> 8) & 0x7F);
               snd_soc_component_write(component, M98088_REG_1B_DAI2_CLKCFG_LO,
                       ni & 0xFF);
       }

       /* Update sample rate mode */
       if (rate < 50000)
               snd_soc_component_update_bits(component, M98088_REG_20_DAI2_FILTERS,
                       M98088_DAI_DHF, 0);
       else
               snd_soc_component_update_bits(component, M98088_REG_20_DAI2_FILTERS,
                       M98088_DAI_DHF, M98088_DAI_DHF);

       snd_soc_component_update_bits(component, M98088_REG_51_PWR_SYS, M98088_SHDNRUN,
               M98088_SHDNRUN);

       return 0;
}