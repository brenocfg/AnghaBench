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
struct resword {int token; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int NR_KEYWORDS ; 
 struct resword* keywords ; 
 int /*<<< orphan*/  memcmp (char const*,int /*<<< orphan*/ ,unsigned int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_reserved_word(register const char *str, register unsigned int len)
{
	int i;
	for (i = 0; i < NR_KEYWORDS; i++) {
		struct resword *r = keywords + i;
		int l = strlen(r->name);
		if (len == l && !memcmp(str, r->name, len))
			return r->token;
	}
	return -1;
}