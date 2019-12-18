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
struct ssl_async_args {TYPE_1__* s; } ;
struct TYPE_3__ {int (* handshake_func ) (TYPE_1__*) ;} ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 int stub1 (TYPE_1__*) ; 

__attribute__((used)) static int ssl_do_handshake_intern(void *vargs)
{
    struct ssl_async_args *args;
    SSL *s;

    args = (struct ssl_async_args *)vargs;
    s = args->s;

    return s->handshake_func(s);
}