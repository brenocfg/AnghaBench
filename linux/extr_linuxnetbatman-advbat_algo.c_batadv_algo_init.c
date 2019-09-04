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

/* Variables and functions */
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_algo_list ; 

void batadv_algo_init(void)
{
	INIT_HLIST_HEAD(&batadv_algo_list);
}