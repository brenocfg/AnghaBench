#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char const* hostname; } ;
struct TYPE_9__ {TYPE_3__ ext; TYPE_2__* session; scalar_t__ hit; } ;
struct TYPE_6__ {char const* hostname; } ;
struct TYPE_7__ {TYPE_1__ ext; } ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 int const TLSEXT_NAMETYPE_host_name ; 

const char *SSL_get_servername(const SSL *s, const int type)
{
    if (type != TLSEXT_NAMETYPE_host_name)
        return NULL;

    /*
     * SNI is not negotiated in pre-TLS-1.3 resumption flows, so fake up an
     * SNI value to return if we are resuming/resumed.  N.B. that we still
     * call the relevant callbacks for such resumption flows, and callbacks
     * might error out if there is not a SNI value available.
     */
    if (s->hit)
        return s->session->ext.hostname;
    return s->ext.hostname;
}