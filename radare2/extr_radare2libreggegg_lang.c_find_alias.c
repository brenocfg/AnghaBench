#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nalias; TYPE_1__* aliases; } ;
struct TYPE_7__ {TYPE_2__ lang; } ;
struct TYPE_5__ {char const* content; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ REgg ;

/* Variables and functions */
 int /*<<< orphan*/  is_space (char) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 char const* strdup (char const*) ; 

__attribute__((used)) static const char *find_alias(REgg *egg, const char *str) {
	// do not forget to free return strings to avoid memory leak
	char *p = (char *) str;
	int i;
	if (*str == '"') {
		return strdup (str);
	}
	// strings could not means aliases
	while (*p && !is_space (*p)) {
		p++;
	}
	*p = '\x00';
	for (i = 0; i < egg->lang.nalias; i++) {
		if (!strcmp (str, egg->lang.aliases[i].name)) {
			return strdup (egg->lang.aliases[i].content);
		}
	}
	return NULL;
	// only strings or alias could return valuable data
}