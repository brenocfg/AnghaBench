#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pid_persist; } ;
struct TYPE_3__ {int /*<<< orphan*/  timeval; int /*<<< orphan*/  packet_id_persist_interval; } ;
struct context {TYPE_2__ c1; TYPE_1__ c2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETT_DEFAULT ; 
 scalar_t__ event_timeout_trigger (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ packet_id_persist_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_id_persist_save (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
check_packet_id_persist_flush(struct context *c)
{
    if (packet_id_persist_enabled(&c->c1.pid_persist)
        && event_timeout_trigger(&c->c2.packet_id_persist_interval, &c->c2.timeval, ETT_DEFAULT))
    {
        packet_id_persist_save(&c->c1.pid_persist);
    }
}