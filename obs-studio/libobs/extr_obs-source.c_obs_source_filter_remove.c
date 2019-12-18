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
typedef  int /*<<< orphan*/  obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  obs_ptr_valid (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ obs_source_filter_remove_refless (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_valid (int /*<<< orphan*/ *,char*) ; 

void obs_source_filter_remove(obs_source_t *source, obs_source_t *filter)
{
	if (!obs_source_valid(source, "obs_source_filter_remove"))
		return;
	if (!obs_ptr_valid(filter, "obs_source_filter_remove"))
		return;

	if (obs_source_filter_remove_refless(source, filter))
		obs_source_release(filter);
}