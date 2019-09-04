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
struct vo {struct priv* priv; } ;
struct priv {int /*<<< orphan*/  vt_switcher; scalar_t__ vt_switcher_active; } ;
typedef  int int64_t ;

/* Variables and functions */
 int MPCLAMP (int,int /*<<< orphan*/ ,int) ; 
 int mp_time_us () ; 
 int /*<<< orphan*/  vo_wait_default (struct vo*,int) ; 
 int /*<<< orphan*/  vt_switcher_poll (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void wait_events(struct vo *vo, int64_t until_time_us)
{
    struct priv *p = vo->priv;
    if (p->vt_switcher_active) {
        int64_t wait_us = until_time_us - mp_time_us();
        int timeout_ms = MPCLAMP((wait_us + 500) / 1000, 0, 10000);
        vt_switcher_poll(&p->vt_switcher, timeout_ms);
    } else {
        vo_wait_default(vo, until_time_us);
    }
}