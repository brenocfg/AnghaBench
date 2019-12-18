#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct extstore_page_data {int dummy; } ;
struct extstore_conf_file {scalar_t__ fd; scalar_t__ page_count; int free_bucket; scalar_t__ offset; struct extstore_conf_file* next; int /*<<< orphan*/  file; } ;
struct extstore_conf {int page_size; int wbuf_size; int page_buckets; int wbuf_count; int io_threadcount; int /*<<< orphan*/  io_depth; } ;
typedef  int /*<<< orphan*/  store_page ;
typedef  int /*<<< orphan*/  store_maint_thread ;
typedef  int /*<<< orphan*/  store_io_thread ;
struct TYPE_10__ {int page_count; int page_size; void* page_data; } ;
struct TYPE_12__ {int page_size; int page_count; int page_bucketcount; int version; int io_threadcount; TYPE_7__* maint_thread; TYPE_7__* io_threads; int /*<<< orphan*/  io_depth; int /*<<< orphan*/  stats_mutex; int /*<<< orphan*/  mutex; TYPE_4__* io_stack; TYPE_5__* wbuf_stack; void* page_buckets; TYPE_1__ stats; TYPE_2__* pages; TYPE_2__** free_page_buckets; TYPE_2__* page_freelist; int /*<<< orphan*/  page_free; } ;
typedef  TYPE_3__ store_engine ;
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_13__ {struct TYPE_13__* next; } ;
typedef  TYPE_4__ obj_io ;
typedef  enum extstore_res { ____Placeholder_extstore_res } extstore_res ;
struct TYPE_14__ {struct TYPE_14__* next; } ;
typedef  TYPE_5__ _store_wbuf ;
struct TYPE_15__ {int /*<<< orphan*/  cond; int /*<<< orphan*/  mutex; TYPE_3__* e; } ;
struct TYPE_11__ {int id; scalar_t__ fd; int free_bucket; int free; struct TYPE_11__* next; scalar_t__ offset; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EXTSTORE_INIT_BAD_WBUF_SIZE ; 
 int EXTSTORE_INIT_NEED_MORE_BUCKETS ; 
 int EXTSTORE_INIT_NEED_MORE_WBUF ; 
 int EXTSTORE_INIT_OOM ; 
 int EXTSTORE_INIT_OPEN_FAIL ; 
 int EXTSTORE_INIT_PAGE_WBUF_ALIGNMENT ; 
 int EXTSTORE_INIT_TOO_MANY_PAGES ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 scalar_t__ UINT16_MAX ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  extstore_io_thread ; 
 int /*<<< orphan*/  extstore_maint_thread ; 
 int /*<<< orphan*/  extstore_run_maint (TYPE_3__*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 scalar_t__ open (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* wbuf_new (int) ; 

void *extstore_init(struct extstore_conf_file *fh, struct extstore_conf *cf,
        enum extstore_res *res) {
    int i;
    struct extstore_conf_file *f = NULL;
    pthread_t thread;

    if (cf->page_size % cf->wbuf_size != 0) {
        *res = EXTSTORE_INIT_BAD_WBUF_SIZE;
        return NULL;
    }
    // Should ensure at least one write buffer per potential page
    if (cf->page_buckets > cf->wbuf_count) {
        *res = EXTSTORE_INIT_NEED_MORE_WBUF;
        return NULL;
    }
    if (cf->page_buckets < 1) {
        *res = EXTSTORE_INIT_NEED_MORE_BUCKETS;
        return NULL;
    }

    // TODO: More intelligence around alignment of flash erasure block sizes
    if (cf->page_size % (1024 * 1024 * 2) != 0 ||
        cf->wbuf_size % (1024 * 1024 * 2) != 0) {
        *res = EXTSTORE_INIT_PAGE_WBUF_ALIGNMENT;
        return NULL;
    }

    store_engine *e = calloc(1, sizeof(store_engine));
    if (e == NULL) {
        *res = EXTSTORE_INIT_OOM;
        return NULL;
    }

    e->page_size = cf->page_size;
    uint64_t temp_page_count = 0;
    for (f = fh; f != NULL; f = f->next) {
        f->fd = open(f->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
        if (f->fd < 0) {
            *res = EXTSTORE_INIT_OPEN_FAIL;
#ifdef EXTSTORE_DEBUG
            perror("open");
#endif
            free(e);
            return NULL;
        }
        temp_page_count += f->page_count;
        f->offset = 0;
    }

    if (temp_page_count >= UINT16_MAX) {
        *res = EXTSTORE_INIT_TOO_MANY_PAGES;
        free(e);
        return NULL;
    }
    e->page_count = temp_page_count;

    e->pages = calloc(e->page_count, sizeof(store_page));
    if (e->pages == NULL) {
        *res = EXTSTORE_INIT_OOM;
        // FIXME: loop-close. make error label
        free(e);
        return NULL;
    }

    // interleave the pages between devices
    f = NULL; // start at the first device.
    for (i = 0; i < e->page_count; i++) {
        // find next device with available pages
        while (1) {
            // restart the loop
            if (f == NULL || f->next == NULL) {
                f = fh;
            } else {
                f = f->next;
            }
            if (f->page_count) {
                f->page_count--;
                break;
            }
        }
        pthread_mutex_init(&e->pages[i].mutex, NULL);
        e->pages[i].id = i;
        e->pages[i].fd = f->fd;
        e->pages[i].free_bucket = f->free_bucket;
        e->pages[i].offset = f->offset;
        e->pages[i].free = true;
        f->offset += e->page_size;
    }

    // free page buckets allows the app to organize devices by use case
    e->free_page_buckets = calloc(cf->page_buckets, sizeof(store_page *));
    e->page_bucketcount = cf->page_buckets;

    for (i = e->page_count-1; i > 0; i--) {
        e->page_free++;
        if (e->pages[i].free_bucket == 0) {
            e->pages[i].next = e->page_freelist;
            e->page_freelist = &e->pages[i];
        } else {
            int fb = e->pages[i].free_bucket;
            e->pages[i].next = e->free_page_buckets[fb];
            e->free_page_buckets[fb] = &e->pages[i];
        }
    }

    // 0 is magic "page is freed" version
    e->version = 1;

    // scratch data for stats. TODO: malloc failure handle
    e->stats.page_data =
        calloc(e->page_count, sizeof(struct extstore_page_data));
    e->stats.page_count = e->page_count;
    e->stats.page_size = e->page_size;

    // page buckets lazily have pages assigned into them
    e->page_buckets = calloc(cf->page_buckets, sizeof(store_page *));
    e->page_bucketcount = cf->page_buckets;

    // allocate write buffers
    // also IO's to use for shipping to IO thread
    for (i = 0; i < cf->wbuf_count; i++) {
        _store_wbuf *w = wbuf_new(cf->wbuf_size);
        obj_io *io = calloc(1, sizeof(obj_io));
        /* TODO: on error, loop again and free stack. */
        w->next = e->wbuf_stack;
        e->wbuf_stack = w;
        io->next = e->io_stack;
        e->io_stack = io;
    }

    pthread_mutex_init(&e->mutex, NULL);
    pthread_mutex_init(&e->stats_mutex, NULL);

    e->io_depth = cf->io_depth;

    // spawn threads
    e->io_threads = calloc(cf->io_threadcount, sizeof(store_io_thread));
    for (i = 0; i < cf->io_threadcount; i++) {
        pthread_mutex_init(&e->io_threads[i].mutex, NULL);
        pthread_cond_init(&e->io_threads[i].cond, NULL);
        e->io_threads[i].e = e;
        // FIXME: error handling
        pthread_create(&thread, NULL, extstore_io_thread, &e->io_threads[i]);
    }
    e->io_threadcount = cf->io_threadcount;

    e->maint_thread = calloc(1, sizeof(store_maint_thread));
    e->maint_thread->e = e;
    // FIXME: error handling
    pthread_mutex_init(&e->maint_thread->mutex, NULL);
    pthread_cond_init(&e->maint_thread->cond, NULL);
    pthread_create(&thread, NULL, extstore_maint_thread, e->maint_thread);

    extstore_run_maint(e);

    return (void *)e;
}