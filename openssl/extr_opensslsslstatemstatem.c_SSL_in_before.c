#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ hand_state; scalar_t__ state; } ;
struct TYPE_5__ {TYPE_1__ statem; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 scalar_t__ MSG_FLOW_UNINITED ; 
 scalar_t__ TLS_ST_BEFORE ; 

int SSL_in_before(const SSL *s)
{
    /*
     * Historically being "in before" meant before anything had happened. In the
     * current code though we remain in the "before" state for a while after we
     * have started the handshake process (e.g. as a server waiting for the
     * first message to arrive). There "in before" is taken to mean "in before"
     * and not started any handshake process yet.
     */
    return (s->statem.hand_state == TLS_ST_BEFORE)
        && (s->statem.state == MSG_FLOW_UNINITED);
}