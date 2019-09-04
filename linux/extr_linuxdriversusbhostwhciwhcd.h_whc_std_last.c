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
struct whc_std {int ntds_remaining; } ;

/* Variables and functions */

__attribute__((used)) static inline bool whc_std_last(struct whc_std *std)
{
	return std->ntds_remaining <= 1;
}