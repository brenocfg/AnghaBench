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
struct ceph_mds_client {int /*<<< orphan*/  cap_flushing_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_caps_flush (struct ceph_mds_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wait_caps_flush(struct ceph_mds_client *mdsc,
			    u64 want_flush_tid)
{
	dout("check_caps_flush want %llu\n", want_flush_tid);

	wait_event(mdsc->cap_flushing_wq,
		   check_caps_flush(mdsc, want_flush_tid));

	dout("check_caps_flush ok, flushed thru %llu\n", want_flush_tid);
}