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
struct TYPE_4__ {int in_init; int /*<<< orphan*/  hand_state; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {TYPE_1__ statem; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_FLOW_UNINITED ; 
 int /*<<< orphan*/  TLS_ST_SR_CLNT_HELLO ; 

void ossl_statem_set_hello_verify_done(SSL *s)
{
    s->statem.state = MSG_FLOW_UNINITED;
    s->statem.in_init = 1;
    /*
     * This will get reset (briefly) back to TLS_ST_BEFORE when we enter
     * state_machine() because |state| is MSG_FLOW_UNINITED, but until then any
     * calls to SSL_in_before() will return false. Also calls to
     * SSL_state_string() and SSL_state_string_long() will return something
     * sensible.
     */
    s->statem.hand_state = TLS_ST_SR_CLNT_HELLO;
}