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
 int atoi (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* r_str_ndup (int /*<<< orphan*/ ,int) ; 
 char* r_str_newf (char*,char*,char*) ; 
 int /*<<< orphan*/  skipnum (char const*) ; 
 char* strdup (char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static char *demangle_classname(const char *s) {
	int modlen, len;
	const char *kstr;
	char *ret, *klass, *module;
	if (!strncmp (s, "_TtC", 4)) {
		len = atoi (s + 4);
		modlen = strlen (s + 4);
		if (len >= modlen) {
			return strdup (s);
		}
		module = r_str_ndup (skipnum (s + 4), len);
		kstr = skipnum (s + 4) + len;
		len = atoi (kstr);
		modlen = strlen (kstr);
		if (len >= modlen) {
			free (module);
			return strdup (s);
		}
		klass = r_str_ndup (skipnum (kstr), len);
		ret = r_str_newf ("%s.%s", module, klass);
		free (module);
		free (klass);
	} else {
		ret = strdup (s);
	}
	return ret;
}