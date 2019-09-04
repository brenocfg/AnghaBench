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
struct MPContext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_wakeup_core (struct MPContext*) ; 

__attribute__((used)) static void wakeup_demux(void *pctx)
{
    struct MPContext *mpctx = pctx;
    mp_wakeup_core(mpctx);
}