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
struct ordered_events {int dummy; } ;
typedef  enum oe_flush { ____Placeholder_oe_flush } oe_flush ;

/* Variables and functions */
 int __ordered_events__flush (struct ordered_events*,int,int /*<<< orphan*/ ) ; 

int ordered_events__flush(struct ordered_events *oe, enum oe_flush how)
{
	return __ordered_events__flush(oe, how, 0);
}