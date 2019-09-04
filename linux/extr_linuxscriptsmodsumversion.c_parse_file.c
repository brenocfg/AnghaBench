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
struct md4_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_char (char,struct md4_ctx*) ; 
 char* grab_file (char const*,unsigned long*) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ parse_comment (char*,unsigned long) ; 
 scalar_t__ parse_string (char*,unsigned long,struct md4_ctx*) ; 
 int /*<<< orphan*/  release_file (char*,unsigned long) ; 

__attribute__((used)) static int parse_file(const char *fname, struct md4_ctx *md)
{
	char *file;
	unsigned long i, len;

	file = grab_file(fname, &len);
	if (!file)
		return 0;

	for (i = 0; i < len; i++) {
		/* Collapse and ignore \ and CR. */
		if (file[i] == '\\' && (i+1 < len) && file[i+1] == '\n') {
			i++;
			continue;
		}

		/* Ignore whitespace */
		if (isspace(file[i]))
			continue;

		/* Handle strings as whole units */
		if (file[i] == '"') {
			i += parse_string(file+i, len - i, md);
			continue;
		}

		/* Comments: ignore */
		if (file[i] == '/' && file[i+1] == '*') {
			i += parse_comment(file+i, len - i);
			continue;
		}

		add_char(file[i], md);
	}
	release_file(file, len);
	return 1;
}