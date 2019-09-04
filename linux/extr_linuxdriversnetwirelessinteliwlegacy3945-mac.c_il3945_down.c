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
struct il_priv {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  __il3945_down (struct il_priv*) ; 
 int /*<<< orphan*/  il3945_cancel_deferred_work (struct il_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
il3945_down(struct il_priv *il)
{
	mutex_lock(&il->mutex);
	__il3945_down(il);
	mutex_unlock(&il->mutex);

	il3945_cancel_deferred_work(il);
}