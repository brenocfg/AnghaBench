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
struct regex {int /*<<< orphan*/  pattern; } ;

/* Variables and functions */
 int /*<<< orphan*/ * strnstr (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * strstr (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regex_match_middle(char *str, struct regex *r, int len)
{
	if (!len)
		return strstr(str, r->pattern) != NULL;

	return strnstr(str, r->pattern, len) != NULL;
}