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
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int SSL_SESSION_set1_ticket_appdata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_get_session (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  appdata ; 
 int gen_tick_called ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gen_tick_cb(SSL *s, void *arg)
{
    gen_tick_called = 1;

    return SSL_SESSION_set1_ticket_appdata(SSL_get_session(s), appdata,
                                           strlen(appdata));
}