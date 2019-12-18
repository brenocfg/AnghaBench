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
struct TYPE_3__ {unsigned char const* session_id; scalar_t__ session_id_length; } ;
typedef  TYPE_1__ SSL_SESSION ;

/* Variables and functions */

const unsigned char *SSL_SESSION_get_id(const SSL_SESSION *s, unsigned int *len)
{
    if (len)
        *len = (unsigned int)s->session_id_length;
    return s->session_id;
}