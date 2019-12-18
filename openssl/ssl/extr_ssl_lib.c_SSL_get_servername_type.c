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
struct TYPE_8__ {scalar_t__ hostname; } ;
struct TYPE_9__ {TYPE_3__ ext; TYPE_2__* session; } ;
struct TYPE_6__ {scalar_t__ hostname; } ;
struct TYPE_7__ {TYPE_1__ ext; } ;
typedef  TYPE_4__ SSL ;

/* Variables and functions */
 int TLSEXT_NAMETYPE_host_name ; 

int SSL_get_servername_type(const SSL *s)
{
    if (s->session
        && (!s->ext.hostname ? s->session->
            ext.hostname : s->ext.hostname))
        return TLSEXT_NAMETYPE_host_name;
    return -1;
}