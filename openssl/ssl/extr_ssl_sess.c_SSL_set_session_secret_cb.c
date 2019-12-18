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
typedef  int /*<<< orphan*/  tls_session_secret_cb_fn ;
struct TYPE_4__ {void* session_secret_cb_arg; int /*<<< orphan*/  session_secret_cb; } ;
struct TYPE_5__ {TYPE_1__ ext; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */

int SSL_set_session_secret_cb(SSL *s,
                              tls_session_secret_cb_fn tls_session_secret_cb,
                              void *arg)
{
    if (s == NULL)
        return 0;
    s->ext.session_secret_cb = tls_session_secret_cb;
    s->ext.session_secret_cb_arg = arg;
    return 1;
}