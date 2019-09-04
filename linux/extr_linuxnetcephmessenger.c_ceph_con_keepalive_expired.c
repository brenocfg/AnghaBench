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
struct ceph_connection {int peer_features; int /*<<< orphan*/  last_keepalive_ack; } ;

/* Variables and functions */
 int CEPH_FEATURE_MSGR_KEEPALIVE2 ; 
 int /*<<< orphan*/  jiffies_to_timespec64 (unsigned long,struct timespec64*) ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (struct timespec64*) ; 
 struct timespec64 timespec64_add (int /*<<< orphan*/ ,struct timespec64) ; 
 scalar_t__ timespec64_compare (struct timespec64*,struct timespec64*) ; 

bool ceph_con_keepalive_expired(struct ceph_connection *con,
			       unsigned long interval)
{
	if (interval > 0 &&
	    (con->peer_features & CEPH_FEATURE_MSGR_KEEPALIVE2)) {
		struct timespec64 now;
		struct timespec64 ts;
		ktime_get_real_ts64(&now);
		jiffies_to_timespec64(interval, &ts);
		ts = timespec64_add(con->last_keepalive_ack, ts);
		return timespec64_compare(&now, &ts) >= 0;
	}
	return false;
}