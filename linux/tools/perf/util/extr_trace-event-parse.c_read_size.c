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
struct tep_event {int /*<<< orphan*/  tep; } ;

/* Variables and functions */
 unsigned long long tep_read_number (int /*<<< orphan*/ ,void*,int) ; 

unsigned long long read_size(struct tep_event *event, void *ptr, int size)
{
	return tep_read_number(event->tep, ptr, size);
}