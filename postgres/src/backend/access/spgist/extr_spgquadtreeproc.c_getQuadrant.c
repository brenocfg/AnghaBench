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
typedef  int int16 ;
typedef  int /*<<< orphan*/  Point ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ SPTEST (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  point_above ; 
 int /*<<< orphan*/  point_below ; 
 int /*<<< orphan*/  point_horiz ; 
 int /*<<< orphan*/  point_left ; 
 int /*<<< orphan*/  point_right ; 
 int /*<<< orphan*/  point_vert ; 

__attribute__((used)) static int16
getQuadrant(Point *centroid, Point *tst)
{
	if ((SPTEST(point_above, tst, centroid) ||
		 SPTEST(point_horiz, tst, centroid)) &&
		(SPTEST(point_right, tst, centroid) ||
		 SPTEST(point_vert, tst, centroid)))
		return 1;

	if (SPTEST(point_below, tst, centroid) &&
		(SPTEST(point_right, tst, centroid) ||
		 SPTEST(point_vert, tst, centroid)))
		return 2;

	if ((SPTEST(point_below, tst, centroid) ||
		 SPTEST(point_horiz, tst, centroid)) &&
		SPTEST(point_left, tst, centroid))
		return 3;

	if (SPTEST(point_above, tst, centroid) &&
		SPTEST(point_left, tst, centroid))
		return 4;

	elog(ERROR, "getQuadrant: impossible case");
	return 0;
}