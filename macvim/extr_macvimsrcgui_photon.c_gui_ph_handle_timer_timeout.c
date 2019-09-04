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
typedef  int /*<<< orphan*/  PtWidget_t ;
typedef  int /*<<< orphan*/  PtCallbackInfo_t ;

/* Variables and functions */
 int Pt_CONTINUE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  is_timeout ; 

__attribute__((used)) static int
gui_ph_handle_timer_timeout(PtWidget_t *widget, void *data, PtCallbackInfo_t *info)
{
    is_timeout = TRUE;

    return Pt_CONTINUE;
}