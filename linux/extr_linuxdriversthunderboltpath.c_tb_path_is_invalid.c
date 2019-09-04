#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tb_path {int path_length; TYPE_5__* hops; } ;
struct TYPE_10__ {TYPE_4__* out_port; TYPE_2__* in_port; } ;
struct TYPE_9__ {TYPE_3__* sw; } ;
struct TYPE_8__ {scalar_t__ is_unplugged; } ;
struct TYPE_7__ {TYPE_1__* sw; } ;
struct TYPE_6__ {scalar_t__ is_unplugged; } ;

/* Variables and functions */

bool tb_path_is_invalid(struct tb_path *path)
{
	int i = 0;
	for (i = 0; i < path->path_length; i++) {
		if (path->hops[i].in_port->sw->is_unplugged)
			return true;
		if (path->hops[i].out_port->sw->is_unplugged)
			return true;
	}
	return false;
}