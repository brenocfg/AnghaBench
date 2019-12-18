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
typedef  double Selectivity ;
typedef  int /*<<< orphan*/  FmgrInfo ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 scalar_t__ DatumGetBool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FunctionCall2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double Min (double,double) ; 
 double inet_hist_value_sel (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Selectivity
inet_semi_join_sel(Datum lhs_value,
				   bool mcv_exists, Datum *mcv_values, int mcv_nvalues,
				   bool hist_exists, Datum *hist_values, int hist_nvalues,
				   double hist_weight,
				   FmgrInfo *proc, int opr_codenum)
{
	if (mcv_exists)
	{
		int			i;

		for (i = 0; i < mcv_nvalues; i++)
		{
			if (DatumGetBool(FunctionCall2(proc,
										   lhs_value,
										   mcv_values[i])))
				return 1.0;
		}
	}

	if (hist_exists && hist_weight > 0)
	{
		Selectivity hist_selec;

		/* Commute operator, since we're passing lhs_value on the right */
		hist_selec = inet_hist_value_sel(hist_values, hist_nvalues,
										 lhs_value, -opr_codenum);

		if (hist_selec > 0)
			return Min(1.0, hist_weight * hist_selec);
	}

	return 0.0;
}