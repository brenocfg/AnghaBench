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
struct TYPE_3__ {scalar_t__ timezone; } ;
typedef  TYPE_1__ RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  freez (void*) ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 
 scalar_t__ strdupz (char const*) ; 

__attribute__((used)) static inline void rrdhost_init_timezone(RRDHOST *host, const char *timezone) {
    if(host->timezone && timezone && !strcmp(host->timezone, timezone))
        return;

    void *old = (void *)host->timezone;
    host->timezone = strdupz((timezone && *timezone)?timezone:"unknown");
    freez(old);
}