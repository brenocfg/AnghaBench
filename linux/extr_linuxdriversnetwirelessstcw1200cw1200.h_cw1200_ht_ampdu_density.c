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
struct TYPE_2__ {int ampdu_density; } ;
struct cw1200_ht_info {TYPE_1__ ht_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  cw1200_is_ht (struct cw1200_ht_info const*) ; 

__attribute__((used)) static inline int cw1200_ht_ampdu_density(const struct cw1200_ht_info *ht_info)
{
	if (!cw1200_is_ht(ht_info))
		return 0;
	return ht_info->ht_cap.ampdu_density;
}