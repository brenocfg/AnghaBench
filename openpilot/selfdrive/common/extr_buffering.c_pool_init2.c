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
struct TYPE_4__ {void (* release_cb ) (void*,int) ;void* cb_cookie; } ;
typedef  TYPE_1__ Pool ;

/* Variables and functions */
 int /*<<< orphan*/  pool_init (TYPE_1__*,int) ; 

void pool_init2(Pool *s, int num_bufs,
  void (*release_cb)(void* c, int idx), void* cb_cookie) {

  pool_init(s, num_bufs);
  s->cb_cookie = cb_cookie;
  s->release_cb = release_cb;

}