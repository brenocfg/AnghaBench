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
struct array_info {int /*<<< orphan*/  kids_type; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ ecalloc (int,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct array_info* parse_array_type_info(const char* array_type) {
	struct array_info* ai = NULL;
	if (array_type) {
		ai = (struct array_info*)ecalloc(1, sizeof(struct array_info));
		if (ai) {
			char buf[128], *p;
			snprintf(buf, sizeof(buf), "%s", array_type);
			p = strchr(buf, '[');
			if (p) {
				*p = 0;
			}
			strcpy(ai->kids_type, buf);
		}
	}
	return ai;
}