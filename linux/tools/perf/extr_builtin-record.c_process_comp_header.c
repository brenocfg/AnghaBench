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
struct TYPE_2__ {size_t size; int /*<<< orphan*/  type; } ;
struct perf_record_compressed {TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_RECORD_COMPRESSED ; 

__attribute__((used)) static size_t process_comp_header(void *record, size_t increment)
{
	struct perf_record_compressed *event = record;
	size_t size = sizeof(*event);

	if (increment) {
		event->header.size += increment;
		return increment;
	}

	event->header.type = PERF_RECORD_COMPRESSED;
	event->header.size = size;

	return size;
}