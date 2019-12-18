#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int http_proxy_owned; int socks_proxy_owned; int /*<<< orphan*/ * socks_proxy; int /*<<< orphan*/ * http_proxy; } ;
struct context {TYPE_1__ c1; } ;

/* Variables and functions */
 int /*<<< orphan*/  http_proxy_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socks_proxy_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
uninit_proxy_dowork(struct context *c)
{
    if (c->c1.http_proxy_owned && c->c1.http_proxy)
    {
        http_proxy_close(c->c1.http_proxy);
        c->c1.http_proxy = NULL;
        c->c1.http_proxy_owned = false;
    }
    if (c->c1.socks_proxy_owned && c->c1.socks_proxy)
    {
        socks_proxy_close(c->c1.socks_proxy);
        c->c1.socks_proxy = NULL;
        c->c1.socks_proxy_owned = false;
    }
}