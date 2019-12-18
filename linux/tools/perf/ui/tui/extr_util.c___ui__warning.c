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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int K_ESC ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int ui__question_window (char const*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfprintf (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ui__warning(const char *title, const char *format, va_list args)
{
	char *s;

	if (vasprintf(&s, format, args) > 0) {
		int key;

		key = ui__question_window(title, s, "Press any key...", 0);
		free(s);
		return key;
	}

	fprintf(stderr, "%s\n", title);
	vfprintf(stderr, format, args);
	return K_ESC;
}