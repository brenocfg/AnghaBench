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
struct TYPE_2__ {int /*<<< orphan*/ * array; } ;
struct ctf_writer {TYPE_1__ data; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bt_ctf_field_type_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ctf_writer__cleanup_data(struct ctf_writer *cw)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(cw->data.array); i++)
		bt_ctf_field_type_put(cw->data.array[i]);
}