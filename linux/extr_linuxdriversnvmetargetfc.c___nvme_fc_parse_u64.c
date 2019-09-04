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
typedef  int /*<<< orphan*/  substring_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ match_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
__nvme_fc_parse_u64(substring_t *sstr, u64 *val)
{
	u64 token64;

	if (match_u64(sstr, &token64))
		return -EINVAL;
	*val = token64;

	return 0;
}