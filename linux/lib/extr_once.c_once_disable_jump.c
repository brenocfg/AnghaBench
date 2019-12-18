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
struct static_key_true {int dummy; } ;
struct once_work {int /*<<< orphan*/  work; struct static_key_true* key; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct once_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  once_deferred ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void once_disable_jump(struct static_key_true *key)
{
	struct once_work *w;

	w = kmalloc(sizeof(*w), GFP_ATOMIC);
	if (!w)
		return;

	INIT_WORK(&w->work, once_deferred);
	w->key = key;
	schedule_work(&w->work);
}