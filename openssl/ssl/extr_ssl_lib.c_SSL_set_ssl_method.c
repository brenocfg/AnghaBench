#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ version; int (* ssl_new ) (TYPE_1__*) ;int (* ssl_connect ) (TYPE_1__*) ;int (* ssl_accept ) (TYPE_1__*) ;int /*<<< orphan*/  (* ssl_free ) (TYPE_1__*) ;} ;
struct TYPE_8__ {int (* handshake_func ) (TYPE_1__*) ;TYPE_2__ const* method; } ;
typedef  TYPE_2__ const SSL_METHOD ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int stub2 (TYPE_1__*) ; 

int SSL_set_ssl_method(SSL *s, const SSL_METHOD *meth)
{
    int ret = 1;

    if (s->method != meth) {
        const SSL_METHOD *sm = s->method;
        int (*hf) (SSL *) = s->handshake_func;

        if (sm->version == meth->version)
            s->method = meth;
        else {
            sm->ssl_free(s);
            s->method = meth;
            ret = s->method->ssl_new(s);
        }

        if (hf == sm->ssl_connect)
            s->handshake_func = meth->ssl_connect;
        else if (hf == sm->ssl_accept)
            s->handshake_func = meth->ssl_accept;
    }
    return ret;
}