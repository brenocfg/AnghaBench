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
struct TYPE_3__ {int /*<<< orphan*/  hTheme; } ;
typedef  int /*<<< orphan*/  PUXINI_FILE ;
typedef  TYPE_1__* PTHEME_FILE ;

/* Variables and functions */
 int /*<<< orphan*/  UXINI_LoadINI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szThemesIniResource ; 

PUXINI_FILE MSSTYLES_GetThemeIni(PTHEME_FILE tf)
{
    return UXINI_LoadINI(tf->hTheme, szThemesIniResource);
}