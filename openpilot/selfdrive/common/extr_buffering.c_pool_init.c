#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int num_bufs; int* refcnt; int* ts; int counter; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ Pool ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void pool_init(Pool *s, int num_bufs) {
  assert(num_bufs > 3);

  memset(s, 0, sizeof(*s));
  s->num_bufs = num_bufs;

  s->refcnt = (int*)calloc(num_bufs, sizeof(int));
  s->ts = (int*)calloc(num_bufs, sizeof(int));

  s->counter = 1;

  pthread_mutex_init(&s->lock, NULL);
}