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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int INDENT ; 
 int /*<<< orphan*/  add_hpp_sort_string (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  add_sort_string (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bstack_sort_dimensions ; 
 int /*<<< orphan*/  common_sort_dimensions ; 
 int /*<<< orphan*/  hpp_sort_dimensions ; 
 int /*<<< orphan*/  memory_sort_dimensions ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int strlen (char const*) ; 

const char *sort_help(const char *prefix)
{
	struct strbuf sb;
	char *s;
	int len = strlen(prefix) + INDENT;

	strbuf_init(&sb, 300);
	strbuf_addstr(&sb, prefix);
	add_hpp_sort_string(&sb, hpp_sort_dimensions,
			    ARRAY_SIZE(hpp_sort_dimensions), &len);
	add_sort_string(&sb, common_sort_dimensions,
			    ARRAY_SIZE(common_sort_dimensions), &len);
	add_sort_string(&sb, bstack_sort_dimensions,
			    ARRAY_SIZE(bstack_sort_dimensions), &len);
	add_sort_string(&sb, memory_sort_dimensions,
			    ARRAY_SIZE(memory_sort_dimensions), &len);
	s = strbuf_detach(&sb, NULL);
	strbuf_release(&sb);
	return s;
}