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
struct resource {scalar_t__ flags; scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */

__attribute__((used)) static inline void reset_resource(struct resource *res)
{
	res->start = 0;
	res->end = 0;
	res->flags = 0;
}