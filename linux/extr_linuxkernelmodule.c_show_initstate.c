#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct module_kobject {TYPE_1__* mod; } ;
struct module_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  MODULE_STATE_COMING 130 
#define  MODULE_STATE_GOING 129 
#define  MODULE_STATE_LIVE 128 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static ssize_t show_initstate(struct module_attribute *mattr,
			      struct module_kobject *mk, char *buffer)
{
	const char *state = "unknown";

	switch (mk->mod->state) {
	case MODULE_STATE_LIVE:
		state = "live";
		break;
	case MODULE_STATE_COMING:
		state = "coming";
		break;
	case MODULE_STATE_GOING:
		state = "going";
		break;
	default:
		BUG();
	}
	return sprintf(buffer, "%s\n", state);
}