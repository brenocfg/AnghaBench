#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dstr {int /*<<< orphan*/  array; } ;
struct TYPE_4__ {int /*<<< orphan*/  defaults; } ;
typedef  TYPE_1__ config_t ;

/* Variables and functions */
 int /*<<< orphan*/  config_set_item (TYPE_1__*,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dstr_init (struct dstr*) ; 
 int /*<<< orphan*/  dstr_printf (struct dstr*,char*,double) ; 

void config_set_default_double(config_t *config, const char *section,
			       const char *name, double value)
{
	struct dstr str;
	dstr_init(&str);
	dstr_printf(&str, "%g", value);
	config_set_item(config, &config->defaults, section, name, str.array);
}