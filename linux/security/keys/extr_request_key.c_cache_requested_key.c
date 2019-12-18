#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct task_struct {int /*<<< orphan*/  cached_requested_key; } ;
struct key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_NOTIFY_RESUME ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  key_get (struct key*) ; 
 int /*<<< orphan*/  key_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cache_requested_key(struct key *key)
{
#ifdef CONFIG_KEYS_REQUEST_CACHE
	struct task_struct *t = current;

	key_put(t->cached_requested_key);
	t->cached_requested_key = key_get(key);
	set_tsk_thread_flag(t, TIF_NOTIFY_RESUME);
#endif
}