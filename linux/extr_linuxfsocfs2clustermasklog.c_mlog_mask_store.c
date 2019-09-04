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
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  __mlog_clear_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mlog_set_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_and_bits ; 
 int /*<<< orphan*/  mlog_not_bits ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int) ; 

__attribute__((used)) static ssize_t mlog_mask_store(u64 mask, const char *buf, size_t count)
{
	if (!strncasecmp(buf, "allow", 5)) {
		__mlog_set_u64(mask, mlog_and_bits);
		__mlog_clear_u64(mask, mlog_not_bits);
	} else if (!strncasecmp(buf, "deny", 4)) {
		__mlog_set_u64(mask, mlog_not_bits);
		__mlog_clear_u64(mask, mlog_and_bits);
	} else if (!strncasecmp(buf, "off", 3)) {
		__mlog_clear_u64(mask, mlog_not_bits);
		__mlog_clear_u64(mask, mlog_and_bits);
	} else
		return -EINVAL;

	return count;
}