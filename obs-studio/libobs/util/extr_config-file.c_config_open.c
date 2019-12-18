#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct config_data {int dummy; } ;
typedef  enum config_open_type { ____Placeholder_config_open_type } config_open_type ;
struct TYPE_7__ {int /*<<< orphan*/  sections; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ config_t ;

/* Variables and functions */
 int CONFIG_ERROR ; 
 int CONFIG_OPEN_ALWAYS ; 
 int CONFIG_SUCCESS ; 
 int /*<<< orphan*/  bfree (TYPE_1__*) ; 
 int /*<<< orphan*/  bstrdup (char const*) ; 
 TYPE_1__* bzalloc (int) ; 
 int /*<<< orphan*/  config_close (TYPE_1__*) ; 
 int config_parse_file (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  init_mutex (TYPE_1__*) ; 

int config_open(config_t **config, const char *file,
		enum config_open_type open_type)
{
	int errorcode;
	bool always_open = open_type == CONFIG_OPEN_ALWAYS;

	if (!config)
		return CONFIG_ERROR;

	*config = bzalloc(sizeof(struct config_data));
	if (!*config)
		return CONFIG_ERROR;

	if (!init_mutex(*config)) {
		bfree(*config);
		return CONFIG_ERROR;
	}

	(*config)->file = bstrdup(file);

	errorcode = config_parse_file(&(*config)->sections, file, always_open);

	if (errorcode != CONFIG_SUCCESS) {
		config_close(*config);
		*config = NULL;
	}

	return errorcode;
}