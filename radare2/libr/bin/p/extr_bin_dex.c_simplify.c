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
 int /*<<< orphan*/  r_str_cpy (char*,char*) ; 
 scalar_t__ r_str_rchr (char*,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  r_str_replace_char (char*,char,char) ; 

__attribute__((used)) static char *simplify(char *s) {
	char *p = (char *)r_str_rchr (s, NULL, '/');
	if (p) {
		r_str_cpy (s, p + 1);
	}
	r_str_replace_char (s, '/', '.');
	return s;
}