#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mpv_node {int dummy; } ;
struct TYPE_3__ {int flag; } ;
struct TYPE_4__ {TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPV_FORMAT_FLAG ; 
 TYPE_2__* node_map_add (struct mpv_node*,char const*,int /*<<< orphan*/ ) ; 

void node_map_add_flag(struct mpv_node *dst, const char *key, bool v)
{
    node_map_add(dst, key, MPV_FORMAT_FLAG)->u.flag = v;
}