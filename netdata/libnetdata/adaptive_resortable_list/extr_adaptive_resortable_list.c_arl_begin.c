#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int iteration; scalar_t__ relinkings; scalar_t__ expected; scalar_t__ allocated; scalar_t__ slow; scalar_t__ fast; int rechecks; scalar_t__ wanted; scalar_t__ found; TYPE_2__* head; TYPE_2__* next_keyword; int /*<<< orphan*/  fred; scalar_t__ added; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int flags; struct TYPE_8__* next; struct TYPE_8__* name; TYPE_1__* prev; } ;
struct TYPE_7__ {TYPE_2__* next; } ;
typedef  TYPE_2__ ARL_ENTRY ;
typedef  TYPE_3__ ARL_BASE ;

/* Variables and functions */
 int ARL_ENTRY_FLAG_DYNAMIC ; 
 int ARL_ENTRY_FLAG_EXPECTED ; 
 int ARL_ENTRY_FLAG_FOUND ; 
 int /*<<< orphan*/  arl_expect (TYPE_3__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freez (TYPE_2__*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,...) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

void arl_begin(ARL_BASE *base) {

#ifdef NETDATA_INTERNAL_CHECKS
    if(likely(base->iteration > 10)) {
        // do these checks after the ARL has been sorted

        if(unlikely(base->relinkings > (base->expected + base->allocated)))
            info("ARL '%s' has %zu relinkings with %zu expected and %zu allocated entries. Is the source changing so fast?"
                 , base->name, base->relinkings, base->expected, base->allocated);

        if(unlikely(base->slow > base->fast))
            info("ARL '%s' has %zu fast searches and %zu slow searches. Is the source really changing so fast?"
                 , base->name, base->fast, base->slow);

        /*
        if(unlikely(base->iteration % 60 == 0)) {
            info("ARL '%s' statistics: iteration %zu, expected %zu, wanted %zu, allocated %zu, fred %zu, relinkings %zu, found %zu, added %zu, fast %zu, slow %zu"
                 , base->name
                 , base->iteration
                 , base->expected
                 , base->wanted
                 , base->allocated
                 , base->fred
                 , base->relinkings
                 , base->found
                 , base->added
                 , base->fast
                 , base->slow
            );
            // for(e = base->head; e; e = e->next) fprintf(stderr, "%s ", e->name);
            // fprintf(stderr, "\n");
        }
        */
    }
#endif

    if(unlikely(base->iteration > 0 && (base->added || (base->iteration % base->rechecks) == 0))) {
        int wanted_equals_expected = ((base->iteration % base->rechecks) == 0);

        // fprintf(stderr, "\n\narl_begin() rechecking, added %zu, iteration %zu, rechecks %zu, wanted_equals_expected %d\n\n\n", base->added, base->iteration, base->rechecks, wanted_equals_expected);

        base->added = 0;
        base->wanted = (wanted_equals_expected)?base->expected:0;

        ARL_ENTRY *e = base->head;
        while(e) {
            if(e->flags & ARL_ENTRY_FLAG_FOUND) {

                // remove the found flag
                e->flags &= ~ARL_ENTRY_FLAG_FOUND;

                // count it in wanted
                if(!wanted_equals_expected && e->flags & ARL_ENTRY_FLAG_EXPECTED)
                    base->wanted++;

            }
            else if(e->flags & ARL_ENTRY_FLAG_DYNAMIC && !(base->head == e && !e->next)) { // not last entry
                // we can remove this entry
                // it is not found, and it was created because
                // it was found in the source file

                // remember the next one
                ARL_ENTRY *t = e->next;

                // remove it from the list
                if(e->next) e->next->prev = e->prev;
                if(e->prev) e->prev->next = e->next;
                if(base->head == e) base->head = e->next;

                // free it
                freez(e->name);
                freez(e);

                // count it
                base->fred++;

                // continue
                e = t;
                continue;
            }

            e = e->next;
        }
    }

    if(unlikely(!base->head)) {
        // hm... no nodes at all in the list #1700
        // add a fake one to prevent a crash
        // this is better than checking for the existence of nodes all the time
        arl_expect(base, "a-really-not-existing-source-keyword", NULL);
    }

    base->iteration++;
    base->next_keyword = base->head;
    base->found = 0;

}