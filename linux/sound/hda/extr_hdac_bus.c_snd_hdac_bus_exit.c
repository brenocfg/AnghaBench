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
struct hdac_bus {int /*<<< orphan*/  unsol_work; int /*<<< orphan*/  codec_list; int /*<<< orphan*/  stream_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void snd_hdac_bus_exit(struct hdac_bus *bus)
{
	WARN_ON(!list_empty(&bus->stream_list));
	WARN_ON(!list_empty(&bus->codec_list));
	cancel_work_sync(&bus->unsol_work);
}