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
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int MAX_CONSIDERED_ELEMS ; 
 scalar_t__ inet_hist_value_sel (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static Selectivity
inet_hist_inclusion_join_sel(Datum *hist1_values, int hist1_nvalues,
							 Datum *hist2_values, int hist2_nvalues,
							 int opr_codenum)
{
	double		match = 0.0;
	int			i,
				k,
				n;

	if (hist2_nvalues <= 2)
		return 0.0;				/* no interior histogram elements */

	/* if there are too many histogram elements, decimate to limit runtime */
	k = (hist2_nvalues - 3) / MAX_CONSIDERED_ELEMS + 1;

	n = 0;
	for (i = 1; i < hist2_nvalues - 1; i += k)
	{
		match += inet_hist_value_sel(hist1_values, hist1_nvalues,
									 hist2_values[i], opr_codenum);
		n++;
	}

	return match / n;
}