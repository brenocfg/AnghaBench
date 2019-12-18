#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fast; int slow; int expected; int allocated; int iteration; scalar_t__ found; scalar_t__ wanted; TYPE_1__* head; TYPE_1__* next_keyword; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int dst; struct TYPE_5__* next; int /*<<< orphan*/  hash; int /*<<< orphan*/  name; int /*<<< orphan*/  (* processor ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ;int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ ARL_ENTRY ;
typedef  TYPE_2__ ARL_BASE ;

/* Variables and functions */
 int /*<<< orphan*/  ARL_ENTRY_FLAG_FOUND ; 
 int arl_find_or_create_and_relink (TYPE_2__*,char const*,char const*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int arl_check(ARL_BASE *base, const char *keyword, const char *value) {
    ARL_ENTRY *e = base->next_keyword;

#ifdef NETDATA_INTERNAL_CHECKS
    if(unlikely((base->fast + base->slow) % (base->expected + base->allocated) == 0 && (base->fast + base->slow) > (base->expected + base->allocated) * base->iteration))
        info("ARL '%s': Did you forget to call arl_begin()?", base->name);
#endif

    // it should be the first entry (pointed by base->next_keyword)
    if(likely(!strcmp(keyword, e->name))) {
        // it is

#ifdef NETDATA_INTERNAL_CHECKS
        base->fast++;
#endif

        e->flags |= ARL_ENTRY_FLAG_FOUND;

        // execute the processor
        if(unlikely(e->dst)) {
            e->processor(e->name, e->hash, value, e->dst);
            base->found++;
        }

        // be prepared for the next iteration
        base->next_keyword = e->next;
        if(unlikely(!base->next_keyword))
            base->next_keyword = base->head;

        // stop if we collected all the values for this iteration
        if(unlikely(base->found == base->wanted)) {
            // fprintf(stderr, "FOUND ALL WANTED 2: found = %zu, wanted = %zu, expected %zu\n", base->found, base->wanted, base->expected);
            return 1;
        }

        return 0;
    }

#ifdef NETDATA_INTERNAL_CHECKS
    base->slow++;
#endif

    // we read from source, a not-expected keyword
    return arl_find_or_create_and_relink(base, keyword, value);
}