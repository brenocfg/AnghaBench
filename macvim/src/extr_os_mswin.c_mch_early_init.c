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
 int /*<<< orphan*/  AnsiLowerBuff (int*,int) ; 
 int /*<<< orphan*/  AnsiUpperBuff (int*,int) ; 
 int /*<<< orphan*/  CharLowerBuff (int*,int) ; 
 int /*<<< orphan*/  CharUpperBuff (int*,int) ; 
 int /*<<< orphan*/  PlatformId () ; 
 int /*<<< orphan*/  get_cmd_argsW (int /*<<< orphan*/ *) ; 
 int* tolower_tab ; 
 int* toupper_tab ; 

void
mch_early_init(void)
{
    int		i;

#ifdef WIN3264
    PlatformId();
#endif

    /* Init the tables for toupper() and tolower() */
    for (i = 0; i < 256; ++i)
	toupper_tab[i] = tolower_tab[i] = i;
#ifdef WIN3264
    CharUpperBuff(toupper_tab, 256);
    CharLowerBuff(tolower_tab, 256);
#else
    AnsiUpperBuff(toupper_tab, 256);
    AnsiLowerBuff(tolower_tab, 256);
#endif

#if defined(FEAT_MBYTE) && !defined(FEAT_GUI)
    (void)get_cmd_argsW(NULL);
#endif
}