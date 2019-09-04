#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double* m_dCurrentPosition; } ;
typedef  TYPE_1__ TGraphCtrl ;

/* Variables and functions */
 int /*<<< orphan*/  GraphCtrl_DrawPoint (TYPE_1__*) ; 

double GraphCtrl_AppendPoint(TGraphCtrl* this,
                             double dNewPoint0, double dNewPoint1,
                             double dNewPoint2, double dNewPoint3)
{
    /*  append a data point to the plot & return the previous point */
    double dPrevious;

    dPrevious = this->m_dCurrentPosition[0];
    this->m_dCurrentPosition[0] = dNewPoint0;
    this->m_dCurrentPosition[1] = dNewPoint1;
    this->m_dCurrentPosition[2] = dNewPoint2;
    this->m_dCurrentPosition[3] = dNewPoint3;
    GraphCtrl_DrawPoint(this);
    /* Invalidate(); */
    return dPrevious;
}