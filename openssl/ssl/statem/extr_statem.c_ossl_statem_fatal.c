#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int in_init; scalar_t__ state; scalar_t__ enc_write_state; } ;
struct TYPE_6__ {TYPE_1__ statem; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 scalar_t__ ENC_WRITE_STATE_INVALID ; 
 int /*<<< orphan*/  ERR_LIB_SSL ; 
 int /*<<< orphan*/  ERR_raise (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERR_set_debug (char const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ MSG_FLOW_ERROR ; 
 int /*<<< orphan*/  SSL3_AL_FATAL ; 
 int SSL_AD_NO_ALERT ; 
 int /*<<< orphan*/  ssl3_send_alert (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void ossl_statem_fatal(SSL *s, int al, int func, int reason, const char *file,
                       int line)
{
    ERR_raise(ERR_LIB_SSL, reason);
    ERR_set_debug(file, line, NULL); /* Override what ERR_raise set */
    /* We shouldn't call SSLfatal() twice. Once is enough */
    if (s->statem.in_init && s->statem.state == MSG_FLOW_ERROR)
      return;
    s->statem.in_init = 1;
    s->statem.state = MSG_FLOW_ERROR;
    if (al != SSL_AD_NO_ALERT
            && s->statem.enc_write_state != ENC_WRITE_STATE_INVALID)
        ssl3_send_alert(s, SSL3_AL_FATAL, al);
}