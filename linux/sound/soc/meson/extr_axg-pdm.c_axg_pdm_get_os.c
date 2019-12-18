#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int ds; } ;
struct axg_pdm_filters {TYPE_3__* lpf; TYPE_2__ hcic; } ;
struct axg_pdm {TYPE_1__* cfg; } ;
struct TYPE_6__ {unsigned int ds; } ;
struct TYPE_4__ {struct axg_pdm_filters* filters; } ;

/* Variables and functions */
 int PDM_LPF_NUM ; 

__attribute__((used)) static unsigned int axg_pdm_get_os(struct axg_pdm *priv)
{
	const struct axg_pdm_filters *filters = priv->cfg->filters;
	unsigned int os = filters->hcic.ds;
	int i;

	/*
	 * The global oversampling factor is defined by the down sampling
	 * factor applied by each filter (HCIC and LPFs)
	 */

	for (i = 0; i < PDM_LPF_NUM; i++)
		os *= filters->lpf[i].ds;

	return os;
}