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
struct script_config {size_t index; int /*<<< orphan*/  extra_format; int /*<<< orphan*/ * paths; int /*<<< orphan*/ * names; } ;

/* Variables and functions */
 size_t SCRIPT_MAX_NO ; 
 scalar_t__ asprintf (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  strstarts (char const*,char*) ; 

__attribute__((used)) static int scripts_config(const char *var, const char *value, void *data)
{
	struct script_config *c = data;

	if (!strstarts(var, "scripts."))
		return -1;
	if (c->index >= SCRIPT_MAX_NO)
		return -1;
	c->names[c->index] = strdup(var + 7);
	if (!c->names[c->index])
		return -1;
	if (asprintf(&c->paths[c->index], "%s %s", value,
		     c->extra_format) < 0)
		return -1;
	c->index++;
	return 0;
}