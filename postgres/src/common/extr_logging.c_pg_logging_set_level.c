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
typedef  enum pg_log_level { ____Placeholder_pg_log_level } pg_log_level ;

/* Variables and functions */
 int __pg_log_level ; 

void
pg_logging_set_level(enum pg_log_level new_level)
{
	__pg_log_level = new_level;
}