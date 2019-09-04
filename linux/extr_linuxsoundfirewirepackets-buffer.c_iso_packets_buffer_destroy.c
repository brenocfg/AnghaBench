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
struct iso_packets_buffer {int /*<<< orphan*/  packets; int /*<<< orphan*/  iso_buffer; } ;
struct fw_unit {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  fw_iso_buffer_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* fw_parent_device (struct fw_unit*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void iso_packets_buffer_destroy(struct iso_packets_buffer *b,
				struct fw_unit *unit)
{
	fw_iso_buffer_destroy(&b->iso_buffer, fw_parent_device(unit)->card);
	kfree(b->packets);
}