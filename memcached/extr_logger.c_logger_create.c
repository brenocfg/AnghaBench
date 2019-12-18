#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  entry_map; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ logger ;
struct TYPE_9__ {int /*<<< orphan*/  logger_buf_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  L_DEBUG (char*) ; 
 int /*<<< orphan*/ * bipbuf_new (int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  default_entries ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  logger_key ; 
 int /*<<< orphan*/  logger_link_q (TYPE_1__*) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__ settings ; 

logger *logger_create(void) {
    L_DEBUG("LOGGER: Creating and linking new logger instance\n");
    logger *l = calloc(1, sizeof(logger));
    if (l == NULL) {
        return NULL;
    }

    l->buf = bipbuf_new(settings.logger_buf_size);
    if (l->buf == NULL) {
        free(l);
        return NULL;
    }

    l->entry_map = default_entries;

    pthread_mutex_init(&l->mutex, NULL);
    pthread_setspecific(logger_key, l);

    /* add to list of loggers */
    logger_link_q(l);
    return l;
}