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
struct packet_id_persist {int fd; scalar_t__ id_last_written; scalar_t__ id; scalar_t__ time_last_written; scalar_t__ time; int /*<<< orphan*/ * filename; } ;

/* Variables and functions */

void
packet_id_persist_init(struct packet_id_persist *p)
{
    p->filename = NULL;
    p->fd = -1;
    p->time = p->time_last_written = 0;
    p->id = p->id_last_written = 0;
}