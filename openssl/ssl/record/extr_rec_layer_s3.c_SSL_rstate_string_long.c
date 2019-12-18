#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int rstate; } ;
struct TYPE_5__ {TYPE_1__ rlayer; } ;
typedef  TYPE_2__ SSL ;

/* Variables and functions */
#define  SSL_ST_READ_BODY 130 
#define  SSL_ST_READ_DONE 129 
#define  SSL_ST_READ_HEADER 128 

const char *SSL_rstate_string_long(const SSL *s)
{
    switch (s->rlayer.rstate) {
    case SSL_ST_READ_HEADER:
        return "read header";
    case SSL_ST_READ_BODY:
        return "read body";
    case SSL_ST_READ_DONE:
        return "read done";
    default:
        return "unknown";
    }
}