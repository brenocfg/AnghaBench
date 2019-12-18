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
struct regex {int len; int /*<<< orphan*/  pattern; } ;

/* Variables and functions */
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int regex_match_end(char *str, struct regex *r, int len)
{
	int strlen = len - 1;

	if (strlen >= r->len &&
	    memcmp(str + strlen - r->len, r->pattern, r->len) == 0)
		return 1;
	return 0;
}