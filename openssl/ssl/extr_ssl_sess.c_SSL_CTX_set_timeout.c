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
struct TYPE_3__ {long session_timeout; } ;
typedef  TYPE_1__ SSL_CTX ;

/* Variables and functions */

long SSL_CTX_set_timeout(SSL_CTX *s, long t)
{
    long l;
    if (s == NULL)
        return 0;
    l = s->session_timeout;
    s->session_timeout = t;
    return l;
}