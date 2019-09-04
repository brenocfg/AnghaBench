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
struct TYPE_3__ {int num_bufs; scalar_t__* refcnt; int /*<<< orphan*/  cb_cookie; int /*<<< orphan*/  (* release_cb ) (int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ Pool ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pool_release_locked(Pool *s, int idx) {
  // printf("release %d refcnt %d\n", idx, s->refcnt[idx]);

  assert(idx >= 0 && idx < s->num_bufs);

  assert(s->refcnt[idx] > 0);
  s->refcnt[idx]--;

  // printf("release %d -> %d, %p\n", idx, s->refcnt[idx], s->release_cb);
  if (s->refcnt[idx] == 0 && s->release_cb) {
    // printf("call %p\b", s->release_cb);
    s->release_cb(s->cb_cookie, idx);
  }
}