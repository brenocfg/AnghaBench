#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  avl ;
struct TYPE_14__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_13__ {char const* name; int /*<<< orphan*/  events; TYPE_2__* first; int /*<<< orphan*/  metrics; int /*<<< orphan*/  index; int /*<<< orphan*/  default_options; } ;
struct TYPE_11__ {TYPE_8__* ext; } ;
struct TYPE_12__ {struct TYPE_12__* next; scalar_t__ name; TYPE_1__ histogram; int /*<<< orphan*/  options; scalar_t__ type; int /*<<< orphan*/  hash; } ;
typedef  scalar_t__ STATSD_METRIC_TYPE ;
typedef  int /*<<< orphan*/  STATSD_METRIC_HISTOGRAM_EXTENSIONS ;
typedef  TYPE_2__ STATSD_METRIC ;
typedef  TYPE_3__ STATSD_INDEX ;

/* Variables and functions */
 int /*<<< orphan*/  D_STATSD ; 
 scalar_t__ STATSD_AVL_INSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STATSD_FIRST_PTR_MUTEX_LOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  STATSD_FIRST_PTR_MUTEX_UNLOCK (TYPE_3__*) ; 
 scalar_t__ STATSD_METRIC_TYPE_HISTOGRAM ; 
 scalar_t__ STATSD_METRIC_TYPE_TIMER ; 
 TYPE_8__* callocz (int,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  freez (void*) ; 
 int /*<<< orphan*/  netdata_mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_hash (char const*) ; 
 TYPE_2__* statsd_metric_index_find (TYPE_3__*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strdupz (char const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline STATSD_METRIC *statsd_find_or_add_metric(STATSD_INDEX *index, const char *name, STATSD_METRIC_TYPE type) {
    debug(D_STATSD, "searching for metric '%s' under '%s'", name, index->name);

    uint32_t hash = simple_hash(name);

    STATSD_METRIC *m = statsd_metric_index_find(index, name, hash);
    if(unlikely(!m)) {
        debug(D_STATSD, "Creating new %s metric '%s'", index->name, name);

        m = (STATSD_METRIC *)callocz(sizeof(STATSD_METRIC), 1);
        m->name = strdupz(name);
        m->hash = hash;
        m->type = type;
        m->options = index->default_options;

        if(type == STATSD_METRIC_TYPE_HISTOGRAM || type == STATSD_METRIC_TYPE_TIMER) {
            m->histogram.ext = callocz(sizeof(STATSD_METRIC_HISTOGRAM_EXTENSIONS), 1);
            netdata_mutex_init(&m->histogram.ext->mutex);
        }
        STATSD_METRIC *n = (STATSD_METRIC *)STATSD_AVL_INSERT(&index->index, (avl *)m);
        if(unlikely(n != m)) {
            freez((void *)m->histogram.ext);
            freez((void *)m->name);
            freez((void *)m);
            m = n;
        }
        else {
            STATSD_FIRST_PTR_MUTEX_LOCK(index);
            index->metrics++;
            m->next = index->first;
            index->first = m;
            STATSD_FIRST_PTR_MUTEX_UNLOCK(index);
        }
    }

    index->events++;
    return m;
}