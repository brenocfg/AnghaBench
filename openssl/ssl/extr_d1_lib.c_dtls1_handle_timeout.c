#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* d1; } ;
struct TYPE_11__ {int read_timeouts; } ;
struct TYPE_12__ {TYPE_1__ timeout; int /*<<< orphan*/  timeout_duration_us; int /*<<< orphan*/  (* timer_cb ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ SSL ;

/* Variables and functions */
 int DTLS1_TMO_READ_COUNT ; 
 scalar_t__ dtls1_check_timeout_num (TYPE_3__*) ; 
 int /*<<< orphan*/  dtls1_double_timeout (TYPE_3__*) ; 
 int /*<<< orphan*/  dtls1_is_timer_expired (TYPE_3__*) ; 
 int dtls1_retransmit_buffered_messages (TYPE_3__*) ; 
 int /*<<< orphan*/  dtls1_start_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

int dtls1_handle_timeout(SSL *s)
{
    /* if no timer is expired, don't do anything */
    if (!dtls1_is_timer_expired(s)) {
        return 0;
    }

    if (s->d1->timer_cb != NULL)
        s->d1->timeout_duration_us = s->d1->timer_cb(s, s->d1->timeout_duration_us);
    else
        dtls1_double_timeout(s);

    if (dtls1_check_timeout_num(s) < 0) {
        /* SSLfatal() already called */
        return -1;
    }

    s->d1->timeout.read_timeouts++;
    if (s->d1->timeout.read_timeouts > DTLS1_TMO_READ_COUNT) {
        s->d1->timeout.read_timeouts = 1;
    }

    dtls1_start_timer(s);
    /* Calls SSLfatal() if required */
    return dtls1_retransmit_buffered_messages(s);
}