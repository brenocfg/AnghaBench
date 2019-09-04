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
typedef  int /*<<< orphan*/  u16 ;
struct ida {int dummy; } ;
struct gb_host_device {struct ida cport_id_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (struct ida*,int /*<<< orphan*/ ) ; 

void gb_hd_cport_release_reserved(struct gb_host_device *hd, u16 cport_id)
{
	struct ida *id_map = &hd->cport_id_map;

	ida_simple_remove(id_map, cport_id);
}