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
struct TYPE_4__ {int /*<<< orphan*/  m_crBackColor; int /*<<< orphan*/  m_brushBack; } ;
typedef  TYPE_1__ TGraphCtrl ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GraphCtrl_InvalidateCtrl (TYPE_1__*,int /*<<< orphan*/ ) ; 

void GraphCtrl_SetBackgroundColor(TGraphCtrl* this, COLORREF color)
{
    this->m_crBackColor = color;
    DeleteObject(this->m_brushBack);
    this->m_brushBack = CreateSolidBrush(this->m_crBackColor);
    /*  clear out the existing garbage, re-start with a clean plot */
    GraphCtrl_InvalidateCtrl(this, FALSE);
}