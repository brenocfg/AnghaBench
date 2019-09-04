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
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct zd_mac {TYPE_1__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_chip_set_rts_cts_rate_locked (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static void set_rts_cts(struct zd_mac *mac, unsigned int short_preamble)
{
	mutex_lock(&mac->chip.mutex);
	zd_chip_set_rts_cts_rate_locked(&mac->chip, short_preamble);
	mutex_unlock(&mac->chip.mutex);
}