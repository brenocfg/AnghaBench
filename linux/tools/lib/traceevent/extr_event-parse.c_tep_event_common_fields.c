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
struct tep_format_field {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  common_fields; int /*<<< orphan*/  nr_common; } ;
struct tep_event {TYPE_1__ format; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct tep_format_field** get_event_fields (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct tep_format_field **tep_event_common_fields(struct tep_event *event)
{
	return get_event_fields("common", event->name,
				event->format.nr_common,
				event->format.common_fields);
}