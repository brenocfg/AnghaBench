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
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  r_return_val_if_fail (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char *__filterQuotedShell(const char *arg) {
	r_return_val_if_fail (arg, NULL);
	char *a = malloc (strlen (arg) + 1);
	if (!a) {
		return NULL;
	}
	char *b = a;
	while (*arg) {
		switch (*arg) {
		case ' ':
		case '=':
		case '"':
		case '\\':
		case '\r':
		case '\n':
			break;
		default:
			*b++ = *arg;
			break;
		}
		arg++;
	}
	*b = 0;
	return a;
}