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
typedef  int u8 ;
struct il_priv {int /*<<< orphan*/  stop_reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  _il_wake_queue (struct il_priv*,int) ; 
 scalar_t__ test_and_clear_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
il_wake_queues_by_reason(struct il_priv *il, int reason)
{
	u8 ac;

	if (test_and_clear_bit(reason, &il->stop_reason))
		for (ac = 0; ac < 4; ac++)
			_il_wake_queue(il, ac);
}