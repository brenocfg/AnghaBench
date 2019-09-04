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
struct TYPE_3__ {int num_bufs; int* reading; int /*<<< orphan*/  cb_cookie; int /*<<< orphan*/  (* release_cb ) (int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_1__ TBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void tbuffer_release_locked(TBuffer *tb, int idx) {
  assert(idx < tb->num_bufs);
  if (!tb->reading[idx]) {
    printf("!! releasing tbuffer we aren't reading %d\n", idx);
  }

  if (tb->release_cb) {
    tb->release_cb(tb->cb_cookie, idx);
  }

  tb->reading[idx] = false;
}