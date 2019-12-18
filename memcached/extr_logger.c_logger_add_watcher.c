#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int sfd; int id; int /*<<< orphan*/ * buf; int /*<<< orphan*/  eflags; int /*<<< orphan*/  t; void* c; } ;
typedef  TYPE_1__ logger_watcher ;
typedef  enum logger_add_watcher_ret { ____Placeholder_logger_add_watcher_ret } logger_add_watcher_ret ;
struct TYPE_7__ {int /*<<< orphan*/  logger_watcher_buf_size; } ;

/* Variables and functions */
 int LOGGER_ADD_WATCHER_FAILED ; 
 int LOGGER_ADD_WATCHER_OK ; 
 int LOGGER_ADD_WATCHER_TOO_MANY ; 
 int /*<<< orphan*/  LOGGER_WATCHER_CLIENT ; 
 int /*<<< orphan*/  LOGGER_WATCHER_STDERR ; 
 int WATCHER_LIMIT ; 
 int /*<<< orphan*/ * bipbuf_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bipbuf_offer (int /*<<< orphan*/ *,unsigned char*,int) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  logger_set_flags () ; 
 int /*<<< orphan*/  logger_stack_lock ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__ settings ; 
 int watcher_count ; 
 TYPE_1__** watchers ; 

enum logger_add_watcher_ret logger_add_watcher(void *c, const int sfd, uint16_t f) {
    int x;
    logger_watcher *w = NULL;
    pthread_mutex_lock(&logger_stack_lock);
    if (watcher_count >= WATCHER_LIMIT) {
        pthread_mutex_unlock(&logger_stack_lock);
        return LOGGER_ADD_WATCHER_TOO_MANY;
    }

    for (x = 0; x < WATCHER_LIMIT-1; x++) {
        if (watchers[x] == NULL)
            break;
    }

    w = calloc(1, sizeof(logger_watcher));
    if (w == NULL) {
        pthread_mutex_unlock(&logger_stack_lock);
        return LOGGER_ADD_WATCHER_FAILED;
    }
    w->c = c;
    w->sfd = sfd;
    if (sfd == 0 && c == NULL) {
        w->t = LOGGER_WATCHER_STDERR;
    } else {
        w->t = LOGGER_WATCHER_CLIENT;
    }
    w->id = x;
    w->eflags = f;
    w->buf = bipbuf_new(settings.logger_watcher_buf_size);
    if (w->buf == NULL) {
        free(w);
        pthread_mutex_unlock(&logger_stack_lock);
        return LOGGER_ADD_WATCHER_FAILED;
    }
    bipbuf_offer(w->buf, (unsigned char *) "OK\r\n", 4);

    watchers[x] = w;
    watcher_count++;
    /* Update what flags the global logs will watch */
    logger_set_flags();

    pthread_mutex_unlock(&logger_stack_lock);
    return LOGGER_ADD_WATCHER_OK;
}