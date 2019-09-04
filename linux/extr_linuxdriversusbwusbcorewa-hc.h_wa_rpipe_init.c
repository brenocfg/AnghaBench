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
struct wahc {int /*<<< orphan*/  rpipe_mutex; int /*<<< orphan*/  rpipe_lock; int /*<<< orphan*/  rpipe_delayed_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void wa_rpipe_init(struct wahc *wa)
{
	INIT_LIST_HEAD(&wa->rpipe_delayed_list);
	spin_lock_init(&wa->rpipe_lock);
	mutex_init(&wa->rpipe_mutex);
}