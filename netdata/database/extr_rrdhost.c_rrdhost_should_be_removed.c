#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_6__ {scalar_t__ senders_disconnected_time; int /*<<< orphan*/  connected_senders; } ;
typedef  TYPE_1__ RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  RRDHOST_FLAG_ORPHAN ; 
 TYPE_1__* localhost ; 
 scalar_t__ rrdhost_flag_check (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ rrdhost_free_orphan_time ; 

inline int rrdhost_should_be_removed(RRDHOST *host, RRDHOST *protected, time_t now) {
    if(host != protected
       && host != localhost
       && rrdhost_flag_check(host, RRDHOST_FLAG_ORPHAN)
       && !host->connected_senders
       && host->senders_disconnected_time
       && host->senders_disconnected_time + rrdhost_free_orphan_time < now)
        return 1;

    return 0;
}