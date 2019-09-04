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
typedef  void i2400m_fw ;
struct i2400m {int /*<<< orphan*/  rx_lock; int /*<<< orphan*/ * fw_cached; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2400m_fw_put (void*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void i2400m_fw_uncache(struct i2400m *i2400m)
{
	struct i2400m_fw *i2400m_fw;

	spin_lock(&i2400m->rx_lock);
	i2400m_fw = i2400m->fw_cached;
	i2400m->fw_cached = NULL;
	spin_unlock(&i2400m->rx_lock);

	if (i2400m_fw != NULL && i2400m_fw != (void *) ~0)
		i2400m_fw_put(i2400m_fw);
}