#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  cloudlog_bind_locked (char const*,char const*) ; 
 int /*<<< orphan*/  cloudlog_init () ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ s ; 

void cloudlog_bind(const char* k, const char* v) {
  pthread_mutex_lock(&s.lock);
  cloudlog_init();
  cloudlog_bind_locked(k, v);
  pthread_mutex_unlock(&s.lock);
}