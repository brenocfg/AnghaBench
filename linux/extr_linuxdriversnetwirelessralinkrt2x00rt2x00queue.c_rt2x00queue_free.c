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
struct rt2x00_dev {int /*<<< orphan*/ * bcn; int /*<<< orphan*/ * tx; int /*<<< orphan*/ * rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void rt2x00queue_free(struct rt2x00_dev *rt2x00dev)
{
	kfree(rt2x00dev->rx);
	rt2x00dev->rx = NULL;
	rt2x00dev->tx = NULL;
	rt2x00dev->bcn = NULL;
}