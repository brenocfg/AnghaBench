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
struct duplicator_capture {int dummy; } ;
typedef  int /*<<< orphan*/  obs_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  update_settings (struct duplicator_capture*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void duplicator_capture_update(void *data, obs_data_t *settings)
{
	struct duplicator_capture *mc = data;
	update_settings(mc, settings);
}