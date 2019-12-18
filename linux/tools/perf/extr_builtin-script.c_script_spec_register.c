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
struct scripting_ops {int dummy; } ;
struct script_spec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  script_spec__add (struct script_spec*) ; 
 struct script_spec* script_spec__find (char const*) ; 
 struct script_spec* script_spec__new (char const*,struct scripting_ops*) ; 

int script_spec_register(const char *spec, struct scripting_ops *ops)
{
	struct script_spec *s;

	s = script_spec__find(spec);
	if (s)
		return -1;

	s = script_spec__new(spec, ops);
	if (!s)
		return -1;
	else
		script_spec__add(s);

	return 0;
}