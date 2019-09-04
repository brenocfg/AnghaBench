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
struct mpv_node {int dummy; } ;

/* Variables and functions */
 int json_append_str (char**,struct mpv_node*,int /*<<< orphan*/ ) ; 

int json_write_pretty(char **dst, struct mpv_node *src)
{
    return json_append_str(dst, src, 0);
}