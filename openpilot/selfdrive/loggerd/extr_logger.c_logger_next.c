#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* segment_path; } ;
struct TYPE_7__ {int part; int /*<<< orphan*/  lock; TYPE_2__* cur_handle; } ;
typedef  TYPE_1__ LoggerState ;
typedef  TYPE_2__ LoggerHandle ;

/* Variables and functions */
 int /*<<< orphan*/  lh_close (TYPE_2__*) ; 
 TYPE_2__* logger_open (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*) ; 

int logger_next(LoggerState *s, const char* root_path,
                            char* out_segment_path, size_t out_segment_path_len,
                            int* out_part) {
  pthread_mutex_lock(&s->lock);
  s->part++;

  LoggerHandle* next_h = logger_open(s, root_path);
  if (!next_h) {
    pthread_mutex_unlock(&s->lock);
    return -1;
  }

  if (s->cur_handle) {
    lh_close(s->cur_handle);
  }
  s->cur_handle = next_h;

  if (out_segment_path) {
    snprintf(out_segment_path, out_segment_path_len, "%s", next_h->segment_path);
  }
  if (out_part) {
    *out_part = s->part;
  }

  pthread_mutex_unlock(&s->lock);
  return 0;
}