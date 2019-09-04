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
struct TYPE_2__ {unsigned int first; unsigned int last; } ;
struct Source {TYPE_1__ port; } ;

/* Variables and functions */

int is_my_port(const struct Source *src, unsigned port)
{
    return src->port.first <= port && port <= src->port.last;
}