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

/* Variables and functions */
 unsigned short HIF_EVENT_MASK ; 

__attribute__((used)) static inline bool is_hif_ind(unsigned short event)
{
	return (((event & HIF_EVENT_MASK) == HIF_EVENT_MASK) &&
		(((event & ~HIF_EVENT_MASK) == 0x0001) ||
		 ((event & ~HIF_EVENT_MASK) == 0x0006) ||
		 ((event & ~HIF_EVENT_MASK) == 0x000C) ||
		 ((event & ~HIF_EVENT_MASK) == 0x0011) ||
		 ((event & ~HIF_EVENT_MASK) == 0x0012)));
}