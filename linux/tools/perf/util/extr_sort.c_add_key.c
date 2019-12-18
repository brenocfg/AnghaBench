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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int INDENT ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void add_key(struct strbuf *sb, const char *str, int *llen)
{
	if (*llen >= 75) {
		strbuf_addstr(sb, "\n\t\t\t ");
		*llen = INDENT;
	}
	strbuf_addf(sb, " %s", str);
	*llen += strlen(str) + 1;
}