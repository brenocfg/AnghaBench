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
typedef  int /*<<< orphan*/  RRDSET ;
typedef  int /*<<< orphan*/  RRDHOST ;

/* Variables and functions */
 int /*<<< orphan*/  D_RRD_CALLS ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * rrdset_find (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  rrdset_isnot_obsolete (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline RRDSET *rrdset_find_on_create(RRDHOST *host, const char *fullid) {
    RRDSET *st = rrdset_find(host, fullid);
    if(unlikely(st)) {
        rrdset_isnot_obsolete(st);
        debug(D_RRD_CALLS, "RRDSET '%s', already exists.", fullid);
        return st;
    }

    return NULL;
}