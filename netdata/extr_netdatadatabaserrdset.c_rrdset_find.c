#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hostname; } ;
typedef  int /*<<< orphan*/  RRDSET ;
typedef  TYPE_1__ RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  D_RRD_CALLS ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rrdset_index_find (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

inline RRDSET *rrdset_find(RRDHOST *host, const char *id) {
    debug(D_RRD_CALLS, "rrdset_find() for chart '%s' in host '%s'", id, host->hostname);
    RRDSET *st = rrdset_index_find(host, id, 0);
    return(st);
}