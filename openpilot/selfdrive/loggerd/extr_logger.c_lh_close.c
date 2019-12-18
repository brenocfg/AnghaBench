#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  lock_path; scalar_t__ log_file; scalar_t__ qlog_file; int /*<<< orphan*/ * bz_qlog; int /*<<< orphan*/ * bz_file; } ;
typedef  TYPE_1__ LoggerHandle ;

/* Variables and functions */
 int /*<<< orphan*/  BZ2_bzWriteClose (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void lh_close(LoggerHandle* h) {
  pthread_mutex_lock(&h->lock);
  assert(h->refcnt > 0);
  h->refcnt--;
  if (h->refcnt == 0) {
    if (h->bz_file){
      int bzerror;
      BZ2_bzWriteClose(&bzerror, h->bz_file, 0, NULL, NULL);
      h->bz_file = NULL;
    }
    if (h->bz_qlog){
      int bzerror;
      BZ2_bzWriteClose(&bzerror, h->bz_qlog, 0, NULL, NULL);
      h->bz_qlog = NULL;
    }
    if (h->qlog_file) fclose(h->qlog_file);
    fclose(h->log_file);
    unlink(h->lock_path);
    pthread_mutex_unlock(&h->lock);
    pthread_mutex_destroy(&h->lock);
    return;
  }
  pthread_mutex_unlock(&h->lock);
}