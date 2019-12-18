#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sk_argument; } ;
typedef  TYPE_1__* ScanKey ;
typedef  int /*<<< orphan*/  Point ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetBoxP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * DatumGetPointP (int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 double point_box_distance (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 double point_point_distance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

double *
spg_key_orderbys_distances(Datum key, bool isLeaf,
						   ScanKey orderbys, int norderbys)
{
	int			sk_num;
	double	   *distances = (double *) palloc(norderbys * sizeof(double)),
			   *distance = distances;

	for (sk_num = 0; sk_num < norderbys; ++sk_num, ++orderbys, ++distance)
	{
		Point	   *point = DatumGetPointP(orderbys->sk_argument);

		*distance = isLeaf ? point_point_distance(point, DatumGetPointP(key))
			: point_box_distance(point, DatumGetBoxP(key));
	}

	return distances;
}