#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ unique; int /*<<< orphan*/ * dict; } ;
struct TYPE_7__ {int reset; int /*<<< orphan*/  count; int /*<<< orphan*/  events; TYPE_1__ set; } ;
typedef  TYPE_2__ STATSD_METRIC ;

/* Variables and functions */
 int DICTIONARY_FLAG_VALUE_LINK_DONT_CLONE ; 
 int STATSD_DICTIONARY_OPTIONS ; 
 int /*<<< orphan*/ * dictionary_create (int) ; 
 int /*<<< orphan*/  dictionary_destroy (int /*<<< orphan*/ *) ; 
 void* dictionary_get (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  dictionary_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  is_metric_useful_for_collection (TYPE_2__*) ; 
 scalar_t__ likely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  statsd_reset_metric (TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 
 int value_is_zinit (char const*) ; 

__attribute__((used)) static inline void statsd_process_set(STATSD_METRIC *m, const char *value) {
    if(!is_metric_useful_for_collection(m)) return;

    if(unlikely(!value || !*value)) {
        error("STATSD: metric of type set, with empty value is ignored.");
        return;
    }

    if(unlikely(m->reset)) {
        if(likely(m->set.dict)) {
            dictionary_destroy(m->set.dict);
            m->set.dict = NULL;
        }
        statsd_reset_metric(m);
    }

    if (unlikely(!m->set.dict)) {
        m->set.dict   = dictionary_create(STATSD_DICTIONARY_OPTIONS | DICTIONARY_FLAG_VALUE_LINK_DONT_CLONE);
        m->set.unique = 0;
    }

    if(unlikely(value_is_zinit(value))) {
        // magic loading of metric, without affecting anything
    }
    else {
        void *t = dictionary_get(m->set.dict, value);
        if (unlikely(!t)) {
            dictionary_set(m->set.dict, value, NULL, 1);
            m->set.unique++;
        }

        m->events++;
        m->count++;
    }
}