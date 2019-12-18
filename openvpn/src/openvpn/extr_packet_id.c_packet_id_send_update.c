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
struct packet_id_send {scalar_t__ time; scalar_t__ id; } ;

/* Variables and functions */
 scalar_t__ PACKET_ID_MAX ; 
 scalar_t__ now ; 

__attribute__((used)) static bool
packet_id_send_update(struct packet_id_send *p, bool long_form)
{
    if (!p->time)
    {
        p->time = now;
    }
    if (p->id == PACKET_ID_MAX)
    {
        /* Packet ID only allowed to roll over if using long form and time has
         * moved forward since last roll over.
         */
        if (!long_form || now <= p->time)
        {
            return false;
        }
        p->time = now;
        p->id = 0;
    }
    p->id++;
    return true;
}