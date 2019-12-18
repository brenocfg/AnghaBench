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
struct tep_event {int dummy; } ;

/* Variables and functions */
 struct tep_event* calloc (int,int) ; 

__attribute__((used)) static struct tep_event *alloc_event(void)
{
	return calloc(1, sizeof(struct tep_event));
}