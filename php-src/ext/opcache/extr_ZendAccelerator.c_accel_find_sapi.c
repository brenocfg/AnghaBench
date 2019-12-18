#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ enable_cli; } ;
struct TYPE_3__ {scalar_t__ name; } ;

/* Variables and functions */
 int FAILURE ; 
 int SUCCESS ; 
 TYPE_2__ ZCG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accel_directives ; 
 TYPE_1__ sapi_module ; 
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static inline int accel_find_sapi(void)
{
	static const char *supported_sapis[] = {
		"apache",
		"fastcgi",
		"cli-server",
		"cgi-fcgi",
		"fpm-fcgi",
		"fpmi-fcgi",
		"apache2handler",
		"litespeed",
		"uwsgi",
		NULL
	};
	const char **sapi_name;

	if (sapi_module.name) {
		for (sapi_name = supported_sapis; *sapi_name; sapi_name++) {
			if (strcmp(sapi_module.name, *sapi_name) == 0) {
				return SUCCESS;
			}
		}
		if (ZCG(accel_directives).enable_cli && (
		    strcmp(sapi_module.name, "cli") == 0
		  || strcmp(sapi_module.name, "phpdbg") == 0)) {
			return SUCCESS;
		}
	}

	return FAILURE;
}