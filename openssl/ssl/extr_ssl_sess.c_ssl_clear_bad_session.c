#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int shutdown; int /*<<< orphan*/ * session; int /*<<< orphan*/  session_ctx; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_remove_session (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int SSL_SENT_SHUTDOWN ; 
 scalar_t__ SSL_in_before (TYPE_1__*) ; 
 scalar_t__ SSL_in_init (TYPE_1__*) ; 

int ssl_clear_bad_session(SSL *s)
{
    if ((s->session != NULL) &&
        !(s->shutdown & SSL_SENT_SHUTDOWN) &&
        !(SSL_in_init(s) || SSL_in_before(s))) {
        SSL_CTX_remove_session(s->session_ctx, s->session);
        return 1;
    } else
        return 0;
}