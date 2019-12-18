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
struct annotation {int nr_events; TYPE_1__* options; } ;
struct TYPE_2__ {scalar_t__ show_total_period; } ;

/* Variables and functions */

__attribute__((used)) static inline int annotation__pcnt_width(struct annotation *notes)
{
	return (notes->options->show_total_period ? 12 : 7) * notes->nr_events;
}