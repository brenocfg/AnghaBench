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

/* Variables and functions */
 int /*<<< orphan*/  errcontext (char*,char const*) ; 
 int /*<<< orphan*/  errposition (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pts_error_callback(void *arg)
{
	const char *str = (const char *) arg;

	errcontext("invalid type name \"%s\"", str);

	/*
	 * Currently we just suppress any syntax error position report, rather
	 * than transforming to an "internal query" error.  It's unlikely that a
	 * type name is complex enough to need positioning.
	 */
	errposition(0);
}