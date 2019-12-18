#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* client_hello_cb_arg; int /*<<< orphan*/  client_hello_cb; } ;
typedef  int /*<<< orphan*/  SSL_client_hello_cb_fn ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */

void SSL_CTX_set_client_hello_cb(SSL_CTX *c, SSL_client_hello_cb_fn cb,
                                 void *arg)
{
    c->client_hello_cb = cb;
    c->client_hello_cb_arg = arg;
}