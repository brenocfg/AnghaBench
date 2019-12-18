#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct event_config {int dummy; } ;
struct conn_queue {int dummy; } ;
typedef  int /*<<< orphan*/  io_wrap ;
struct TYPE_8__ {scalar_t__ ssl_wbuf_size; scalar_t__ ssl_enabled; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_7__ {char* ssl_wbuf; int /*<<< orphan*/ * io_cache; int /*<<< orphan*/ * suffix_cache; TYPE_1__ stats; int /*<<< orphan*/ * new_conn_queue; int /*<<< orphan*/  notify_event; int /*<<< orphan*/  base; int /*<<< orphan*/  notify_receive_fd; } ;
typedef  TYPE_2__ LIBEVENT_THREAD ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_BASE_FLAG_NOLOCK ; 
 int EV_PERSIST ; 
 int EV_READ ; 
 int EXIT_FAILURE ; 
 int SUFFIX_SIZE ; 
 void* cache_create (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cq_init (int /*<<< orphan*/ *) ; 
 int event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_new_with_config (struct event_config*) ; 
 int /*<<< orphan*/  event_base_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_config_free (struct event_config*) ; 
 struct event_config* event_config_new () ; 
 int /*<<< orphan*/  event_config_set_flag (struct event_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_init () ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_4__ settings ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  thread_libevent_process ; 

__attribute__((used)) static void setup_thread(LIBEVENT_THREAD *me) {
#if defined(LIBEVENT_VERSION_NUMBER) && LIBEVENT_VERSION_NUMBER >= 0x02000101
    struct event_config *ev_config;
    ev_config = event_config_new();
    event_config_set_flag(ev_config, EVENT_BASE_FLAG_NOLOCK);
    me->base = event_base_new_with_config(ev_config);
    event_config_free(ev_config);
#else
    me->base = event_init();
#endif

    if (! me->base) {
        fprintf(stderr, "Can't allocate event base\n");
        exit(1);
    }

    /* Listen for notifications from other threads */
    event_set(&me->notify_event, me->notify_receive_fd,
              EV_READ | EV_PERSIST, thread_libevent_process, me);
    event_base_set(me->base, &me->notify_event);

    if (event_add(&me->notify_event, 0) == -1) {
        fprintf(stderr, "Can't monitor libevent notify pipe\n");
        exit(1);
    }

    me->new_conn_queue = malloc(sizeof(struct conn_queue));
    if (me->new_conn_queue == NULL) {
        perror("Failed to allocate memory for connection queue");
        exit(EXIT_FAILURE);
    }
    cq_init(me->new_conn_queue);

    if (pthread_mutex_init(&me->stats.mutex, NULL) != 0) {
        perror("Failed to initialize mutex");
        exit(EXIT_FAILURE);
    }

    me->suffix_cache = cache_create("suffix", SUFFIX_SIZE, sizeof(char*),
                                    NULL, NULL);
    if (me->suffix_cache == NULL) {
        fprintf(stderr, "Failed to create suffix cache\n");
        exit(EXIT_FAILURE);
    }
#ifdef EXTSTORE
    me->io_cache = cache_create("io", sizeof(io_wrap), sizeof(char*), NULL, NULL);
    if (me->io_cache == NULL) {
        fprintf(stderr, "Failed to create IO object cache\n");
        exit(EXIT_FAILURE);
    }
#endif
#ifdef TLS
    if (settings.ssl_enabled) {
        me->ssl_wbuf = (char *)malloc((size_t)settings.ssl_wbuf_size);
        if (me->ssl_wbuf == NULL) {
            fprintf(stderr, "Failed to allocate the SSL write buffer\n");
            exit(EXIT_FAILURE);
        }
    }
#endif
}