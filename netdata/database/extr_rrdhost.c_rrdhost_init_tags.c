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
struct TYPE_3__ {int /*<<< orphan*/ * tags; } ;
typedef  TYPE_1__ RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  freez (void*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * strdupz (char const*) ; 

__attribute__((used)) static inline void rrdhost_init_tags(RRDHOST *host, const char *tags) {
    if(host->tags && tags && !strcmp(host->tags, tags))
        return;

    void *old = (void *)host->tags;
    host->tags = (tags && *tags)?strdupz(tags):NULL;
    freez(old);
}