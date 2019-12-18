#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
#define  SSL3_AL_FATAL 129 
#define  SSL3_AL_WARNING 128 

const char *SSL_alert_type_string_long(int value)
{
    switch (value >> 8) {
    case SSL3_AL_WARNING:
        return "warning";
    case SSL3_AL_FATAL:
        return "fatal";
    default:
        return "unknown";
    }
}