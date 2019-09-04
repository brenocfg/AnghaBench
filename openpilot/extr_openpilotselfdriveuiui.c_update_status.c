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
struct TYPE_3__ {int status; int /*<<< orphan*/  bg_cond; } ;
typedef  TYPE_1__ UIState ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_status(UIState *s, int status) {
  if (s->status != status) {
    s->status = status;
    // wake up bg thread to change
    pthread_cond_signal(&s->bg_cond);
  }
}