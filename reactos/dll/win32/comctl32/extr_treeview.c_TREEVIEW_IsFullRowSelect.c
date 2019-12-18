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
struct TYPE_3__ {int dwStyle; } ;
typedef  TYPE_1__ TREEVIEW_INFO ;
typedef  int BOOL ;

/* Variables and functions */
 int TVS_FULLROWSELECT ; 
 int TVS_HASLINES ; 

__attribute__((used)) static BOOL
TREEVIEW_IsFullRowSelect(const TREEVIEW_INFO *infoPtr)
{
    return !(infoPtr->dwStyle & TVS_HASLINES) && (infoPtr->dwStyle & TVS_FULLROWSELECT);
}