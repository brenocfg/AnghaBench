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
struct config_data {int /*<<< orphan*/  file; } ;
typedef  struct config_data config_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (struct config_data*) ; 
 int /*<<< orphan*/  bstrdup (char const*) ; 
 struct config_data* bzalloc (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_mutex (struct config_data*) ; 
 int /*<<< orphan*/ * os_fopen (char const*,char*) ; 

config_t *config_create(const char *file)
{
	struct config_data *config;
	FILE *f;

	f = os_fopen(file, "wb");
	if (!f)
		return NULL;
	fclose(f);

	config = bzalloc(sizeof(struct config_data));

	if (!init_mutex(config)) {
		bfree(config);
		return NULL;
	}

	config->file = bstrdup(file);
	return config;
}