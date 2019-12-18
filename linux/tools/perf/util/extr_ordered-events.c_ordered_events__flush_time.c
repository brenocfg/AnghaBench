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
typedef  int /*<<< orphan*/  u64 ;
struct ordered_events {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OE_FLUSH__TIME ; 
 int __ordered_events__flush (struct ordered_events*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ordered_events__flush_time(struct ordered_events *oe, u64 timestamp)
{
	return __ordered_events__flush(oe, OE_FLUSH__TIME, timestamp);
}