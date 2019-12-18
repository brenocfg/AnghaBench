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
typedef  scalar_t__ u16 ;
struct dsmark_qdisc_data {scalar_t__ indices; } ;

/* Variables and functions */

__attribute__((used)) static inline int dsmark_valid_index(struct dsmark_qdisc_data *p, u16 index)
{
	return index <= p->indices && index > 0;
}