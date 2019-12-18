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
struct TYPE_7__ {scalar_t__ refcnt; char* segment_path; char* log_path; char* qlog_path; char* lock_path; int /*<<< orphan*/ * log_file; int /*<<< orphan*/ * qlog_file; int /*<<< orphan*/  lock; void* bz_qlog; void* bz_file; } ;
struct TYPE_6__ {char* route_name; int part; char* log_name; int /*<<< orphan*/  init_data_len; int /*<<< orphan*/  init_data; scalar_t__ has_qlog; TYPE_2__* handles; } ;
typedef  TYPE_1__ LoggerState ;
typedef  TYPE_2__ LoggerHandle ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BZ2_bzWrite (int*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* BZ2_bzWriteOpen (int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int BZ_OK ; 
 int /*<<< orphan*/  LOGE (char*) ; 
 int LOGGER_MAX_HANDLES ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 void* fopen (char*,char*) ; 
 int mkpath (char*) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 

__attribute__((used)) static LoggerHandle* logger_open(LoggerState *s, const char* root_path) {
  int err;

  LoggerHandle *h = NULL;
  for (int i=0; i<LOGGER_MAX_HANDLES; i++) {
    if (s->handles[i].refcnt == 0) {
      h = &s->handles[i];
      break;
    }
  }
  assert(h);

  snprintf(h->segment_path, sizeof(h->segment_path),
          "%s/%s--%d", root_path, s->route_name, s->part);

  snprintf(h->log_path, sizeof(h->log_path), "%s/%s.bz2", h->segment_path, s->log_name);
  snprintf(h->qlog_path, sizeof(h->qlog_path), "%s/qlog.bz2", h->segment_path);
  snprintf(h->lock_path, sizeof(h->lock_path), "%s.lock", h->log_path);

  err = mkpath(h->log_path);
  if (err) return NULL;

  FILE* lock_file = fopen(h->lock_path, "wb");
  if (lock_file == NULL) return NULL;
  fclose(lock_file);

  h->log_file = fopen(h->log_path, "wb");
  if (h->log_file == NULL) goto fail;

  if (s->has_qlog) {
    h->qlog_file = fopen(h->qlog_path, "wb");
    if (h->qlog_file == NULL) goto fail;
  }

  int bzerror;
  h->bz_file = BZ2_bzWriteOpen(&bzerror, h->log_file, 9, 0, 30);
  if (bzerror != BZ_OK) goto fail;

  if (s->has_qlog) {
    h->bz_qlog = BZ2_bzWriteOpen(&bzerror, h->qlog_file, 9, 0, 30);
    if (bzerror != BZ_OK) goto fail;
  }

  if (s->init_data) {
    BZ2_bzWrite(&bzerror, h->bz_file, s->init_data, s->init_data_len);
    if (bzerror != BZ_OK) goto fail;

    if (s->has_qlog) {
      // init data goes in the qlog too
      BZ2_bzWrite(&bzerror, h->bz_qlog, s->init_data, s->init_data_len);
      if (bzerror != BZ_OK) goto fail;
    }
  }

  pthread_mutex_init(&h->lock, NULL);
  h->refcnt++;
  return h;
fail:
  LOGE("logger failed to open files");
  if (h->qlog_file) fclose(h->qlog_file);
  if (h->log_file) fclose(h->log_file);
  return NULL;
}