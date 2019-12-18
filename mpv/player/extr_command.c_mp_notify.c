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
struct MPContext {int osd_idle_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  command_event (struct MPContext*,int,void*) ; 
 int /*<<< orphan*/  mp_client_broadcast_event (struct MPContext*,int,void*) ; 

void mp_notify(struct MPContext *mpctx, int event, void *arg)
{
    // The OSD can implicitly reference some properties.
    mpctx->osd_idle_update = true;

    command_event(mpctx, event, arg);

    mp_client_broadcast_event(mpctx, event, arg);
}