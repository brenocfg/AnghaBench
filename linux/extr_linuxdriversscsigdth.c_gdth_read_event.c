#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  smp_lock; } ;
typedef  TYPE_1__ gdth_ha_str ;
struct TYPE_9__ {scalar_t__ event_source; } ;
typedef  TYPE_2__ gdth_evt_str ;

/* Variables and functions */
 int MAX_EVENTS ; 
 int /*<<< orphan*/  TRACE2 (char*) ; 
 TYPE_2__* ebuffer ; 
 int elastidx ; 
 int eoldidx ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int gdth_read_event(gdth_ha_str *ha, int handle, gdth_evt_str *estr)
{
    gdth_evt_str *e;
    int eindex;
    unsigned long flags;

    TRACE2(("gdth_read_event() handle %d\n", handle));
    spin_lock_irqsave(&ha->smp_lock, flags);
    if (handle == -1)
        eindex = eoldidx;
    else
        eindex = handle;
    estr->event_source = 0;

    if (eindex < 0 || eindex >= MAX_EVENTS) {
        spin_unlock_irqrestore(&ha->smp_lock, flags);
        return eindex;
    }
    e = &ebuffer[eindex];
    if (e->event_source != 0) {
        if (eindex != elastidx) {
            if (++eindex == MAX_EVENTS)
                eindex = 0;
        } else {
            eindex = -1;
        }
        memcpy(estr, e, sizeof(gdth_evt_str));
    }
    spin_unlock_irqrestore(&ha->smp_lock, flags);
    return eindex;
}