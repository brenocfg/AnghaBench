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
struct cpsw_ale {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_ENABLE ; 
 int /*<<< orphan*/  cpsw_ale_control_set (struct cpsw_ale*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

void cpsw_ale_stop(struct cpsw_ale *ale)
{
	del_timer_sync(&ale->timer);
	cpsw_ale_control_set(ale, 0, ALE_ENABLE, 0);
}