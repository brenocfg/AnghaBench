#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct unwind_entry {int /*<<< orphan*/ * sym; int /*<<< orphan*/  map; int /*<<< orphan*/  ip; } ;
struct callchain_cursor {int dummy; } ;
struct TYPE_2__ {scalar_t__ hide_unresolved; } ;

/* Variables and functions */
 scalar_t__ append_inlines (struct callchain_cursor*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int callchain_cursor_append (struct callchain_cursor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 char* callchain_srcline (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map__map_ip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int unwind_entry(struct unwind_entry *entry, void *arg)
{
	struct callchain_cursor *cursor = arg;
	const char *srcline = NULL;
	u64 addr = entry->ip;

	if (symbol_conf.hide_unresolved && entry->sym == NULL)
		return 0;

	if (append_inlines(cursor, entry->map, entry->sym, entry->ip) == 0)
		return 0;

	/*
	 * Convert entry->ip from a virtual address to an offset in
	 * its corresponding binary.
	 */
	if (entry->map)
		addr = map__map_ip(entry->map, entry->ip);

	srcline = callchain_srcline(entry->map, entry->sym, addr);
	return callchain_cursor_append(cursor, entry->ip,
				       entry->map, entry->sym,
				       false, NULL, 0, 0, 0, srcline);
}