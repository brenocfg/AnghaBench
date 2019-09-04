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
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_cons_readpush (char*,int) ; 
 int r_str_unescape (char*) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int cmd_pipein(void *user, const char *input) {
	char *buf = strdup (input);
	int len = r_str_unescape (buf);
	r_cons_readpush (buf, len);
	free (buf);
	return 0;
}