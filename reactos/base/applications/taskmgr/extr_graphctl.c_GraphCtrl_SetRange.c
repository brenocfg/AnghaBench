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
struct TYPE_4__ {double m_dLowerLimit; double m_dUpperLimit; int m_nYDecimals; double m_dRange; double m_dVerticalFactor; scalar_t__ m_nPlotHeight; } ;
typedef  TYPE_1__ TGraphCtrl ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GraphCtrl_InvalidateCtrl (TYPE_1__*,int /*<<< orphan*/ ) ; 

void GraphCtrl_SetRange(TGraphCtrl* this, double dLower, double dUpper, int nDecimalPlaces)
{
    /* ASSERT(dUpper > dLower); */
    this->m_dLowerLimit     = dLower;
    this->m_dUpperLimit     = dUpper;
    this->m_nYDecimals      = nDecimalPlaces;
    this->m_dRange          = this->m_dUpperLimit - this->m_dLowerLimit;
    this->m_dVerticalFactor = (double)this->m_nPlotHeight / this->m_dRange;
    /*  clear out the existing garbage, re-start with a clean plot */
    GraphCtrl_InvalidateCtrl(this, FALSE);
}