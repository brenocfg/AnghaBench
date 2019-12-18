#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int http_proxy_owned; int socks_proxy_owned; scalar_t__ socks_proxy; scalar_t__ http_proxy; } ;
struct TYPE_4__ {int /*<<< orphan*/  socks_proxy_authfile; int /*<<< orphan*/  socks_proxy_port; scalar_t__ socks_proxy_server; scalar_t__ http_proxy_options; } ;
struct TYPE_5__ {TYPE_1__ ce; } ;
struct context {TYPE_3__ c1; TYPE_2__ options; } ;

/* Variables and functions */
 scalar_t__ http_proxy_new (scalar_t__) ; 
 scalar_t__ socks_proxy_new (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uninit_proxy_dowork (struct context*) ; 

__attribute__((used)) static void
init_proxy_dowork(struct context *c)
{
    bool did_http = false;

    uninit_proxy_dowork(c);

    if (c->options.ce.http_proxy_options)
    {
        /* Possible HTTP proxy user/pass input */
        c->c1.http_proxy = http_proxy_new(c->options.ce.http_proxy_options);
        if (c->c1.http_proxy)
        {
            did_http = true;
            c->c1.http_proxy_owned = true;
        }
    }

    if (!did_http && c->options.ce.socks_proxy_server)
    {
        c->c1.socks_proxy = socks_proxy_new(c->options.ce.socks_proxy_server,
                                            c->options.ce.socks_proxy_port,
                                            c->options.ce.socks_proxy_authfile);
        if (c->c1.socks_proxy)
        {
            c->c1.socks_proxy_owned = true;
        }
    }
}