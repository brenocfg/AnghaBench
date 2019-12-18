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
struct tls_multi {scalar_t__ locked_cn; TYPE_1__* session; } ;
struct TYPE_2__ {char* common_name; } ;

/* Variables and functions */
 size_t TM_ACTIVE ; 
 scalar_t__ string_alloc (char const*,int /*<<< orphan*/ *) ; 

void
tls_lock_common_name(struct tls_multi *multi)
{
    const char *cn = multi->session[TM_ACTIVE].common_name;
    if (cn && !multi->locked_cn)
    {
        multi->locked_cn = string_alloc(cn, NULL);
    }
}