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
struct gelic_port {struct gelic_card* card; } ;
struct gelic_card {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct gelic_card *port_to_card(struct gelic_port *p)
{
	return p->card;
}