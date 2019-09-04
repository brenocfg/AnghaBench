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
struct TYPE_3__ {unsigned char const* sid_ctx; scalar_t__ sid_ctx_length; } ;
typedef  TYPE_1__ SSL_SESSION ;

/* Variables and functions */

const unsigned char *SSL_SESSION_get0_id_context(const SSL_SESSION *s,
                                                unsigned int *len)
{
    if (len != NULL)
        *len = (unsigned int)s->sid_ctx_length;
    return s->sid_ctx;
}