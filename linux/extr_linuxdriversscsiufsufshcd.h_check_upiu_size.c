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
 scalar_t__ ALIGNED_UPIU_SIZE ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ GENERAL_UPIU_REQUEST_SIZE ; 
 scalar_t__ QUERY_DESC_MAX_SIZE ; 

__attribute__((used)) static inline void check_upiu_size(void)
{
	BUILD_BUG_ON(ALIGNED_UPIU_SIZE <
		GENERAL_UPIU_REQUEST_SIZE + QUERY_DESC_MAX_SIZE);
}