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

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/ * rrdset_find_byname_localhost (char*) ; 
 int /*<<< orphan*/  rrdset_is_obsolete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintfz (char*,int,char*,char*,char const*) ; 

__attribute__((used)) static inline void make_chart_obsolete(char *name, const char *id_modifier) {
    char id[50 + 1];
    RRDSET *st = NULL;

    if(likely(name && id_modifier)) {
        snprintfz(id, 50, "mdstat.%s_%s", name, id_modifier);
        st = rrdset_find_byname_localhost(id);
        if(likely(st)) rrdset_is_obsolete(st);
    }
}