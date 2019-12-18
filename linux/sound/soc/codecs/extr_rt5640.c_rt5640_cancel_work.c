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
struct rt5640_priv {int /*<<< orphan*/  bp_work; int /*<<< orphan*/  jack_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt5640_cancel_work(void *data)
{
	struct rt5640_priv *rt5640 = data;

	cancel_work_sync(&rt5640->jack_work);
	cancel_delayed_work_sync(&rt5640->bp_work);
}