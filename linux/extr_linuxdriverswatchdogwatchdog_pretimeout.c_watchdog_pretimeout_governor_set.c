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
struct watchdog_device {int /*<<< orphan*/  gov; } ;
struct governor_priv {int /*<<< orphan*/  gov; } ;

/* Variables and functions */
 int EINVAL ; 
 struct governor_priv* find_governor_by_name (char const*) ; 
 int /*<<< orphan*/  governor_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pretimeout_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int watchdog_pretimeout_governor_set(struct watchdog_device *wdd,
				     const char *buf)
{
	struct governor_priv *priv;

	mutex_lock(&governor_lock);

	priv = find_governor_by_name(buf);
	if (!priv) {
		mutex_unlock(&governor_lock);
		return -EINVAL;
	}

	spin_lock_irq(&pretimeout_lock);
	wdd->gov = priv->gov;
	spin_unlock_irq(&pretimeout_lock);

	mutex_unlock(&governor_lock);

	return 0;
}