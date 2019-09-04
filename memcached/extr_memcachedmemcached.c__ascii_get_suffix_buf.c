#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int suffixsize; char** suffixlist; TYPE_1__* thread; } ;
typedef  TYPE_2__ conn ;
struct TYPE_8__ {int /*<<< orphan*/  malloc_fails; } ;
struct TYPE_6__ {int /*<<< orphan*/  suffix_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATS_LOCK () ; 
 int /*<<< orphan*/  STATS_UNLOCK () ; 
 char* do_cache_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_of_memory (TYPE_2__*,char*) ; 
 char** realloc (char**,int) ; 
 TYPE_3__ stats ; 

__attribute__((used)) static inline char *_ascii_get_suffix_buf(conn *c, int i) {
    char *suffix;
    /* Goofy mid-flight realloc. */
    if (i >= c->suffixsize) {
    char **new_suffix_list = realloc(c->suffixlist,
                           sizeof(char *) * c->suffixsize * 2);
    if (new_suffix_list) {
        c->suffixsize *= 2;
        c->suffixlist  = new_suffix_list;
    } else {
        STATS_LOCK();
        stats.malloc_fails++;
        STATS_UNLOCK();
        return NULL;
    }
    }

    suffix = do_cache_alloc(c->thread->suffix_cache);
    if (suffix == NULL) {
      STATS_LOCK();
      stats.malloc_fails++;
      STATS_UNLOCK();
      out_of_memory(c, "SERVER_ERROR out of memory making CAS suffix");
      return NULL;
    }
    *(c->suffixlist + i) = suffix;
    return suffix;
}