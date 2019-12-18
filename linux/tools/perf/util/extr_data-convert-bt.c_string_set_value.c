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
struct bt_ctf_field {int dummy; } ;
typedef  int /*<<< orphan*/  string ;
typedef  int /*<<< orphan*/  numstr ;

/* Variables and functions */
 int bt_ctf_field_string_set_value (struct bt_ctf_field*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isprint (char const) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 char* zalloc (size_t) ; 

__attribute__((used)) static int string_set_value(struct bt_ctf_field *field, const char *string)
{
	char *buffer = NULL;
	size_t len = strlen(string), i, p;
	int err;

	for (i = p = 0; i < len; i++, p++) {
		if (isprint(string[i])) {
			if (!buffer)
				continue;
			buffer[p] = string[i];
		} else {
			char numstr[5];

			snprintf(numstr, sizeof(numstr), "\\x%02x",
				 (unsigned int)(string[i]) & 0xff);

			if (!buffer) {
				buffer = zalloc(i + (len - i) * 4 + 2);
				if (!buffer) {
					pr_err("failed to set unprintable string '%s'\n", string);
					return bt_ctf_field_string_set_value(field, "UNPRINTABLE-STRING");
				}
				if (i > 0)
					strncpy(buffer, string, i);
			}
			memcpy(buffer + p, numstr, 4);
			p += 3;
		}
	}

	if (!buffer)
		return bt_ctf_field_string_set_value(field, string);
	err = bt_ctf_field_string_set_value(field, buffer);
	free(buffer);
	return err;
}