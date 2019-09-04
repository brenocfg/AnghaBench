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
typedef  int /*<<< orphan*/  u32 ;
struct smp2p_entry {int /*<<< orphan*/  smp2p; int /*<<< orphan*/  lock; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  qcom_smp2p_kick (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smp2p_update_bits(void *data, u32 mask, u32 value)
{
	struct smp2p_entry *entry = data;
	u32 orig;
	u32 val;

	spin_lock(&entry->lock);
	val = orig = readl(entry->value);
	val &= ~mask;
	val |= value;
	writel(val, entry->value);
	spin_unlock(&entry->lock);

	if (val != orig)
		qcom_smp2p_kick(entry->smp2p);

	return 0;
}