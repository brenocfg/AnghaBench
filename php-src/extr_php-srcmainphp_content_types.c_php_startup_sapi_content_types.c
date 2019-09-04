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
 int SUCCESS ; 
 int /*<<< orphan*/  php_default_input_filter ; 
 int /*<<< orphan*/  php_default_post_reader ; 
 int /*<<< orphan*/  php_default_treat_data ; 
 int /*<<< orphan*/  sapi_register_default_post_reader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sapi_register_input_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sapi_register_treat_data (int /*<<< orphan*/ ) ; 

int php_startup_sapi_content_types(void)
{
	sapi_register_default_post_reader(php_default_post_reader);
	sapi_register_treat_data(php_default_treat_data);
	sapi_register_input_filter(php_default_input_filter, NULL);
	return SUCCESS;
}