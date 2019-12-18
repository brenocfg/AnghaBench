#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tls_multi {TYPE_1__* session; } ;
struct TYPE_2__ {char* common_name; } ;

/* Variables and functions */
 size_t TM_ACTIVE ; 
 scalar_t__ strlen (char const*) ; 

const char *
tls_common_name(const struct tls_multi *multi, const bool null)
{
    const char *ret = NULL;
    if (multi)
    {
        ret = multi->session[TM_ACTIVE].common_name;
    }
    if (ret && strlen(ret))
    {
        return ret;
    }
    else if (null)
    {
        return NULL;
    }
    else
    {
        return "UNDEF";
    }
}