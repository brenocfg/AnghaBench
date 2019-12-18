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
 int /*<<< orphan*/  PG_LOG_INFO ; 
 int /*<<< orphan*/  pg_log_generic (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void
notice_processor(void *arg, const char *message)
{
	pg_log_generic(PG_LOG_INFO, "%s", message);
}