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

/* Variables and functions */
 int /*<<< orphan*/ * g_szOrigTitle ; 
 int /*<<< orphan*/  mch_settitle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
mch_restore_title(
    int which)
{
#ifndef FEAT_GUI_MSWIN
    mch_settitle((which & 1) ? g_szOrigTitle : NULL, NULL);
#endif
}