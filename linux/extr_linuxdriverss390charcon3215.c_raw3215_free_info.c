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
struct raw3215_info {int /*<<< orphan*/  port; struct raw3215_info* buffer; struct raw3215_info* inbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct raw3215_info*) ; 
 int /*<<< orphan*/  tty_port_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raw3215_free_info(struct raw3215_info *raw)
{
	kfree(raw->inbuf);
	kfree(raw->buffer);
	tty_port_destroy(&raw->port);
	kfree(raw);
}