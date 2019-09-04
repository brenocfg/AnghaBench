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
struct tep_plugin_option {scalar_t__ name; } ;
struct registered_plugin_options {struct tep_plugin_option* options; struct registered_plugin_options* next; } ;

/* Variables and functions */
 struct registered_plugin_options* malloc (int) ; 
 struct registered_plugin_options* registered_options ; 
 int /*<<< orphan*/  update_option (char const*,struct tep_plugin_option*) ; 

int tep_plugin_add_options(const char *name,
			   struct tep_plugin_option *options)
{
	struct registered_plugin_options *reg;

	reg = malloc(sizeof(*reg));
	if (!reg)
		return -1;
	reg->next = registered_options;
	reg->options = options;
	registered_options = reg;

	while (options->name) {
		update_option(name, options);
		options++;
	}
	return 0;
}