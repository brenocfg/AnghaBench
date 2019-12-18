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
typedef  int /*<<< orphan*/  uint32_t ;
struct wp_presentation {int dummy; } ;
struct vo_wayland_state {struct wp_presentation* presentation; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 

__attribute__((used)) static void pres_set_clockid(void *data, struct wp_presentation *pres,
                           uint32_t clockid)
{
    struct vo_wayland_state *wl = data;
    
    wl->presentation = pres;
    clockid = CLOCK_MONOTONIC;
}