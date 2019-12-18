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
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ found; int iteration; scalar_t__ wanted; TYPE_1__* head; TYPE_1__* next_keyword; int /*<<< orphan*/  name; int /*<<< orphan*/  added; int /*<<< orphan*/  allocated; int /*<<< orphan*/  relinkings; } ;
struct TYPE_5__ {scalar_t__ hash; int dst; int flags; struct TYPE_5__* next; struct TYPE_5__* prev; int /*<<< orphan*/  name; int /*<<< orphan*/  (* processor ) (int /*<<< orphan*/ ,scalar_t__,char const*,int) ;} ;
typedef  TYPE_1__ ARL_ENTRY ;
typedef  TYPE_2__ ARL_BASE ;

/* Variables and functions */
 int ARL_ENTRY_FLAG_DYNAMIC ; 
 int ARL_ENTRY_FLAG_FOUND ; 
 TYPE_1__* callocz (int,int) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ simple_hash (char const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strdupz (char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,scalar_t__,char const*,int) ; 
 scalar_t__ unlikely (int) ; 

int arl_find_or_create_and_relink(ARL_BASE *base, const char *s, const char *value) {
    ARL_ENTRY *e;

    uint32_t hash = simple_hash(s);

    // find if it already exists in the data
    for(e = base->head; e ; e = e->next)
        if(e->hash == hash && !strcmp(e->name, s))
            break;

#ifdef NETDATA_INTERNAL_CHECKS
    if(unlikely(base->next_keyword && e == base->next_keyword))
        fatal("Internal Error: e == base->last");
#endif

    if(e) {
        // found it in the keywords

        base->relinkings++;

        // run the processor for it
        if(unlikely(e->dst)) {
            e->processor(e->name, hash, value, e->dst);
            base->found++;
        }

        // unlink it - we will relink it below
        if(e->next) e->next->prev = e->prev;
        if(e->prev) e->prev->next = e->next;

        // make sure the head is properly linked
        if(base->head == e)
            base->head = e->next;
    }
    else {
        // not found

        // create it
        e = callocz(1, sizeof(ARL_ENTRY));
        e->name = strdupz(s);
        e->hash = hash;
        e->flags = ARL_ENTRY_FLAG_DYNAMIC;

        base->allocated++;
        base->added++;
    }

#ifdef NETDATA_INTERNAL_CHECKS
    if(unlikely(base->iteration % 60 == 0 && e->flags & ARL_ENTRY_FLAG_FOUND))
        info("ARL '%s': entry '%s' is already found. Did you forget to call arl_begin()?", base->name, s);
#endif

    e->flags |= ARL_ENTRY_FLAG_FOUND;

    // link it here
    e->next = base->next_keyword;
    if(base->next_keyword) {
        e->prev = base->next_keyword->prev;
        base->next_keyword->prev = e;

        if(e->prev)
            e->prev->next = e;

        if(base->head == base->next_keyword)
            base->head = e;
    }
    else {
        e->prev = NULL;

        if(!base->head)
            base->head = e;
    }

    // prepare the next iteration
    base->next_keyword = e->next;
    if(unlikely(!base->next_keyword))
        base->next_keyword = base->head;

    if(unlikely(base->found == base->wanted)) {
        // fprintf(stderr, "FOUND ALL WANTED 1: found = %zu, wanted = %zu, expected %zu\n", base->found, base->wanted, base->expected);
        return 1;
    }

    return 0;
}