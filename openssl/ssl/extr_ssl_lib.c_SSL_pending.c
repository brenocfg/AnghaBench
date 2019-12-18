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
struct TYPE_6__ {TYPE_1__* method; } ;
struct TYPE_5__ {size_t (* ssl_pending ) (TYPE_2__ const*) ;} ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
 size_t INT_MAX ; 
 size_t stub1 (TYPE_2__ const*) ; 

int SSL_pending(const SSL *s)
{
    size_t pending = s->method->ssl_pending(s);

    /*
     * SSL_pending cannot work properly if read-ahead is enabled
     * (SSL_[CTX_]ctrl(..., SSL_CTRL_SET_READ_AHEAD, 1, NULL)), and it is
     * impossible to fix since SSL_pending cannot report errors that may be
     * observed while scanning the new data. (Note that SSL_pending() is
     * often used as a boolean value, so we'd better not return -1.)
     *
     * SSL_pending also cannot work properly if the value >INT_MAX. In that case
     * we just return INT_MAX.
     */
    return pending < INT_MAX ? (int)pending : INT_MAX;
}