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
struct luma_wipe_info {int /*<<< orphan*/  wipes_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  obs_data_create_from_json_file (char*) ; 
 char* obs_module_file (char*) ; 

__attribute__((used)) static void luma_wipe_get_list(void *data)
{
	struct luma_wipe_info *lwipe = data;

	char *path = obs_module_file("luma_wipes/wipes.json");

	lwipe->wipes_list = obs_data_create_from_json_file(path);

	bfree(path);
}