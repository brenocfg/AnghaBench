#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timelib_tzdb_index_entry ;
struct TYPE_3__ {int index_size; int /*<<< orphan*/  const* index; } ;
typedef  TYPE_1__ timelib_tzdb ;

/* Variables and functions */

const timelib_tzdb_index_entry *timelib_timezone_identifiers_list(const timelib_tzdb *tzdb, int *count)
{
	*count = tzdb->index_size;
	return tzdb->index;
}