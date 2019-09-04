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
struct type_tbl_s {int len; int type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 
 struct type_tbl_s* type_tbl ; 

__attribute__((used)) static int get_type(const char *l, const char **t) {
	const struct type_tbl_s *p;

	for (p = type_tbl; p->len; p++) {
		if (strncmp (l, p->name, p->len) == 0) {
			if (t) {
				*t = l + p->len;
			}
			break;
		}
	}
	return p->type;
}