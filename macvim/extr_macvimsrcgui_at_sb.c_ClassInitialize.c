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
typedef  int /*<<< orphan*/  XtConvertArgList ;
typedef  int /*<<< orphan*/  Cardinal ;

/* Variables and functions */
 int /*<<< orphan*/  XawInitializeWidgetSet () ; 
 int /*<<< orphan*/  XmuCvtStringToOrientation ; 
 int /*<<< orphan*/  XtAddConverter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XtROrientation ; 
 int /*<<< orphan*/  XtRString ; 

__attribute__((used)) static void
ClassInitialize()
{
    XawInitializeWidgetSet();
    XtAddConverter( XtRString, XtROrientation, XmuCvtStringToOrientation,
	    (XtConvertArgList)NULL, (Cardinal)0 );
}