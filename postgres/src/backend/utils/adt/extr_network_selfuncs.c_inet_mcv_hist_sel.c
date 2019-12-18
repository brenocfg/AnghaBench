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
typedef  double float4 ;
typedef  double Selectivity ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 double inet_hist_value_sel (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Selectivity
inet_mcv_hist_sel(Datum *mcv_values, float4 *mcv_numbers, int mcv_nvalues,
				  Datum *hist_values, int hist_nvalues,
				  int opr_codenum)
{
	Selectivity selec = 0.0;
	int			i;

	/*
	 * We'll call inet_hist_value_selec with the histogram on the left, so we
	 * must commute the operator.
	 */
	opr_codenum = -opr_codenum;

	for (i = 0; i < mcv_nvalues; i++)
	{
		selec += mcv_numbers[i] *
			inet_hist_value_sel(hist_values, hist_nvalues, mcv_values[i],
								opr_codenum);
	}
	return selec;
}