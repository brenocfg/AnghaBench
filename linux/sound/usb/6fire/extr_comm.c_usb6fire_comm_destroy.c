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
struct sfire_chip {struct comm_runtime* comm; } ;
struct comm_runtime {struct comm_runtime* receiver_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct comm_runtime*) ; 

void usb6fire_comm_destroy(struct sfire_chip *chip)
{
	struct comm_runtime *rt = chip->comm;

	kfree(rt->receiver_buffer);
	kfree(rt);
	chip->comm = NULL;
}