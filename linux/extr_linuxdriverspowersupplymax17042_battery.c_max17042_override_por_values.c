#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct max17042_config_data {int /*<<< orphan*/  kempty0; int /*<<< orphan*/  empty_tempco; int /*<<< orphan*/  tcompc0; int /*<<< orphan*/  rcomp0; int /*<<< orphan*/  fctc; int /*<<< orphan*/  temp_lim; int /*<<< orphan*/  temp_nom; int /*<<< orphan*/  vempty; int /*<<< orphan*/  dpacc; int /*<<< orphan*/  dqacc; int /*<<< orphan*/  lavg_empty; int /*<<< orphan*/  socempty; int /*<<< orphan*/  fullcapnom; int /*<<< orphan*/  fullcap; int /*<<< orphan*/  masksoc; int /*<<< orphan*/  misc_cfg; int /*<<< orphan*/  relax_cfg; int /*<<< orphan*/  filter_cfg; int /*<<< orphan*/  learn_cfg; int /*<<< orphan*/  at_rate; int /*<<< orphan*/  ichgt_term; int /*<<< orphan*/  design_cap; int /*<<< orphan*/  shdntimer; int /*<<< orphan*/  config; int /*<<< orphan*/  soc_alrt_thresh; int /*<<< orphan*/  talrt_thresh; int /*<<< orphan*/  valrt_thresh; int /*<<< orphan*/  coff; int /*<<< orphan*/  cgain; int /*<<< orphan*/  toff; int /*<<< orphan*/  tgain; } ;
struct max17042_chip {scalar_t__ chip_type; TYPE_1__* pdata; struct regmap* regmap; } ;
struct TYPE_2__ {struct max17042_config_data* config_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX17042_AtRate ; 
 int /*<<< orphan*/  MAX17042_CGAIN ; 
 int /*<<< orphan*/  MAX17042_COFF ; 
 int /*<<< orphan*/  MAX17042_CONFIG ; 
 int /*<<< orphan*/  MAX17042_DesignCap ; 
 int /*<<< orphan*/  MAX17042_EmptyTempCo ; 
 int /*<<< orphan*/  MAX17042_FCTC ; 
 int /*<<< orphan*/  MAX17042_FilterCFG ; 
 int /*<<< orphan*/  MAX17042_FullCAP ; 
 int /*<<< orphan*/  MAX17042_FullCAPNom ; 
 int /*<<< orphan*/  MAX17042_ICHGTerm ; 
 int /*<<< orphan*/  MAX17042_K_empty0 ; 
 int /*<<< orphan*/  MAX17042_LAvg_empty ; 
 int /*<<< orphan*/  MAX17042_LearnCFG ; 
 int /*<<< orphan*/  MAX17042_MaskSOC ; 
 int /*<<< orphan*/  MAX17042_MiscCFG ; 
 int /*<<< orphan*/  MAX17042_RCOMP0 ; 
 int /*<<< orphan*/  MAX17042_RelaxCFG ; 
 int /*<<< orphan*/  MAX17042_SALRT_Th ; 
 int /*<<< orphan*/  MAX17042_SHDNTIMER ; 
 int /*<<< orphan*/  MAX17042_SOC_empty ; 
 int /*<<< orphan*/  MAX17042_TALRT_Th ; 
 int /*<<< orphan*/  MAX17042_TGAIN ; 
 int /*<<< orphan*/  MAX17042_TempCo ; 
 int /*<<< orphan*/  MAX17042_TempLim ; 
 int /*<<< orphan*/  MAX17042_TempNom ; 
 int /*<<< orphan*/  MAX17042_VALRT_Th ; 
 int /*<<< orphan*/  MAX17042_V_empty ; 
 int /*<<< orphan*/  MAX17042_dPacc ; 
 int /*<<< orphan*/  MAX17042_dQacc ; 
 int /*<<< orphan*/  MAX17047_V_empty ; 
 scalar_t__ MAXIM_DEVICE_TYPE_MAX17042 ; 
 int /*<<< orphan*/  MAx17042_TOFF ; 
 int /*<<< orphan*/  max17042_override_por (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void max17042_override_por_values(struct max17042_chip *chip)
{
	struct regmap *map = chip->regmap;
	struct max17042_config_data *config = chip->pdata->config_data;

	max17042_override_por(map, MAX17042_TGAIN, config->tgain);
	max17042_override_por(map, MAx17042_TOFF, config->toff);
	max17042_override_por(map, MAX17042_CGAIN, config->cgain);
	max17042_override_por(map, MAX17042_COFF, config->coff);

	max17042_override_por(map, MAX17042_VALRT_Th, config->valrt_thresh);
	max17042_override_por(map, MAX17042_TALRT_Th, config->talrt_thresh);
	max17042_override_por(map, MAX17042_SALRT_Th,
						config->soc_alrt_thresh);
	max17042_override_por(map, MAX17042_CONFIG, config->config);
	max17042_override_por(map, MAX17042_SHDNTIMER, config->shdntimer);

	max17042_override_por(map, MAX17042_DesignCap, config->design_cap);
	max17042_override_por(map, MAX17042_ICHGTerm, config->ichgt_term);

	max17042_override_por(map, MAX17042_AtRate, config->at_rate);
	max17042_override_por(map, MAX17042_LearnCFG, config->learn_cfg);
	max17042_override_por(map, MAX17042_FilterCFG, config->filter_cfg);
	max17042_override_por(map, MAX17042_RelaxCFG, config->relax_cfg);
	max17042_override_por(map, MAX17042_MiscCFG, config->misc_cfg);
	max17042_override_por(map, MAX17042_MaskSOC, config->masksoc);

	max17042_override_por(map, MAX17042_FullCAP, config->fullcap);
	max17042_override_por(map, MAX17042_FullCAPNom, config->fullcapnom);
	if (chip->chip_type == MAXIM_DEVICE_TYPE_MAX17042)
		max17042_override_por(map, MAX17042_SOC_empty,
						config->socempty);
	max17042_override_por(map, MAX17042_LAvg_empty, config->lavg_empty);
	max17042_override_por(map, MAX17042_dQacc, config->dqacc);
	max17042_override_por(map, MAX17042_dPacc, config->dpacc);

	if (chip->chip_type == MAXIM_DEVICE_TYPE_MAX17042)
		max17042_override_por(map, MAX17042_V_empty, config->vempty);
	else
		max17042_override_por(map, MAX17047_V_empty, config->vempty);
	max17042_override_por(map, MAX17042_TempNom, config->temp_nom);
	max17042_override_por(map, MAX17042_TempLim, config->temp_lim);
	max17042_override_por(map, MAX17042_FCTC, config->fctc);
	max17042_override_por(map, MAX17042_RCOMP0, config->rcomp0);
	max17042_override_por(map, MAX17042_TempCo, config->tcompc0);
	if (chip->chip_type) {
		max17042_override_por(map, MAX17042_EmptyTempCo,
						config->empty_tempco);
		max17042_override_por(map, MAX17042_K_empty0,
						config->kempty0);
	}
}