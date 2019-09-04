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
struct htcp {int /*<<< orphan*/  last_cong; int /*<<< orphan*/  old_maxB; int /*<<< orphan*/  undo_old_maxB; int /*<<< orphan*/  maxRTT; int /*<<< orphan*/  undo_maxRTT; int /*<<< orphan*/  undo_last_cong; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static inline void htcp_reset(struct htcp *ca)
{
	ca->undo_last_cong = ca->last_cong;
	ca->undo_maxRTT = ca->maxRTT;
	ca->undo_old_maxB = ca->old_maxB;

	ca->last_cong = jiffies;
}