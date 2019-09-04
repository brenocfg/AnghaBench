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
struct portman {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  portman_flush_input (struct portman*,int) ; 

__attribute__((used)) static int portman_device_init(struct portman *pm)
{
	portman_flush_input(pm, 0);
	portman_flush_input(pm, 1);

	return 0;
}