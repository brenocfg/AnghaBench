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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/ * bz_qlog; int /*<<< orphan*/ * bz_file; } ;
typedef  TYPE_1__ LoggerHandle ;

/* Variables and functions */
 int /*<<< orphan*/  BZ2_bzWrite (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void lh_log(LoggerHandle* h, uint8_t* data, size_t data_size, bool in_qlog) {
  pthread_mutex_lock(&h->lock);
  assert(h->refcnt > 0);
  int bzerror;
  BZ2_bzWrite(&bzerror, h->bz_file, data, data_size);

  if (in_qlog && h->bz_qlog != NULL) {
    BZ2_bzWrite(&bzerror, h->bz_qlog, data, data_size);
  }
  pthread_mutex_unlock(&h->lock);
}