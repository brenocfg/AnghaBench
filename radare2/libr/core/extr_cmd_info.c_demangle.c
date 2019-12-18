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
struct TYPE_4__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  demangle_internal (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_config_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  r_return_val_if_fail (int,int) ; 
 char* strchr (char const*,char) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static bool demangle(RCore *core, const char *s) {
	r_return_val_if_fail (core && s, false);
	const char *ss = strchr (s, ' ');
	if (!*s) {
		return false;
	}
	if (!ss) {
		const char *lang = r_config_get (core->config, "bin.lang");
		demangle_internal (core, lang, s);
		return true;
	}
	char *p = strdup (s);
	char *q = p + (ss - s);
	*q = 0;
	demangle_internal (core, p, q + 1);
	free (p);
	return true;
}