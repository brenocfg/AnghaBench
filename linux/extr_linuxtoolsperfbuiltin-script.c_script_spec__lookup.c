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
struct script_spec {struct scripting_ops* ops; } ;

/* Variables and functions */
 struct script_spec* script_spec__find (char const*) ; 

__attribute__((used)) static struct scripting_ops *script_spec__lookup(const char *spec)
{
	struct script_spec *s = script_spec__find(spec);
	if (!s)
		return NULL;

	return s->ops;
}