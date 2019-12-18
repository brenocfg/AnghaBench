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
struct timespec64 {int dummy; } ;
struct dfs_cache_entry {int /*<<< orphan*/  ce_etime; } ;

/* Variables and functions */
 int /*<<< orphan*/  ktime_get_coarse_real_ts64 (struct timespec64*) ; 
 scalar_t__ timespec64_compare (struct timespec64*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool cache_entry_expired(const struct dfs_cache_entry *ce)
{
	struct timespec64 ts;

	ktime_get_coarse_real_ts64(&ts);
	return timespec64_compare(&ts, &ce->ce_etime) >= 0;
}