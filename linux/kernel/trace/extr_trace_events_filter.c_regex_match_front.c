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
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int regex_match_front(char *str, struct regex *r, int len)
{
	if (len && len < r->len)
		return 0;

	return strncmp(str, r->pattern, r->len) == 0;
}