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
typedef  int Dimension ;

/* Variables and functions */
 int /*<<< orphan*/  XmNshadowThickness ; 
 int /*<<< orphan*/  XtVaGetValues (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  textAreaForm ; 

int
gui_mch_text_area_extra_height()
{
    Dimension	shadowHeight;

    XtVaGetValues(textAreaForm, XmNshadowThickness, &shadowHeight, NULL);
    return shadowHeight;
}