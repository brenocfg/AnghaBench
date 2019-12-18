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
 int RRD_ID_LENGTH_MAX ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rrdset_find (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  strncpyz (char*,char const*,size_t) ; 

inline RRDSET *rrdset_find_bytype(RRDHOST *host, const char *type, const char *id) {
    debug(D_RRD_CALLS, "rrdset_find_bytype() for chart '%s.%s' in host '%s'", type, id, host->hostname);

    char buf[RRD_ID_LENGTH_MAX + 1];
    strncpyz(buf, type, RRD_ID_LENGTH_MAX - 1);
    strcat(buf, ".");
    int len = (int) strlen(buf);
    strncpyz(&buf[len], id, (size_t) (RRD_ID_LENGTH_MAX - len));

    return(rrdset_find(host, buf));
}