#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int index_size; unsigned char* data; TYPE_1__* index; } ;
typedef  TYPE_2__ timelib_tzdb ;
struct TYPE_4__ {size_t pos; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int timelib_strcasecmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int seek_to_tz_position(const unsigned char **tzf, char *timezone, const timelib_tzdb *tzdb)
{
	int left = 0, right = tzdb->index_size - 1;

	if (tzdb->index_size == 0) {
		return 0;
	}

	do {
		int mid = ((unsigned)left + right) >> 1;
		int cmp = timelib_strcasecmp(timezone, tzdb->index[mid].id);

		if (cmp < 0) {
			right = mid - 1;
		} else if (cmp > 0) {
			left = mid + 1;
		} else { /* (cmp == 0) */
			(*tzf) = &(tzdb->data[tzdb->index[mid].pos]);
			return 1;
		}

	} while (left <= right);

	return 0;
}