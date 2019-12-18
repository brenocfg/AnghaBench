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
struct twitch_ingest {int /*<<< orphan*/ * url; int /*<<< orphan*/ * name; } ;
struct TYPE_2__ {size_t num; scalar_t__ array; } ;

/* Variables and functions */
 TYPE_1__ cur_ingests ; 

struct twitch_ingest twitch_ingest(size_t idx)
{
	struct twitch_ingest ingest;

	if (cur_ingests.num <= idx) {
		ingest.name = NULL;
		ingest.url = NULL;
	} else {
		ingest = *(struct twitch_ingest *)(cur_ingests.array + idx);
	}

	return ingest;
}