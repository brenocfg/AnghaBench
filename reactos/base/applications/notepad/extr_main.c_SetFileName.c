#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_2__ {scalar_t__* szFileTitle; scalar_t__* szFileName; } ;
typedef  int /*<<< orphan*/  LPCTSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (scalar_t__*) ; 
 int /*<<< orphan*/  GetFileTitle (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 TYPE_1__ Globals ; 
 int /*<<< orphan*/  StringCchCopy (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VOID SetFileName(LPCTSTR szFileName)
{
    StringCchCopy(Globals.szFileName, ARRAY_SIZE(Globals.szFileName), szFileName);
    Globals.szFileTitle[0] = 0;
    GetFileTitle(szFileName, Globals.szFileTitle, ARRAY_SIZE(Globals.szFileTitle));
}