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
struct ceph_osd_client {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_ON_FULL ; 
 int /*<<< orphan*/  CEPH_OSDMAP_FULL ; 
 int /*<<< orphan*/  abort_on_full_fn ; 
 scalar_t__ ceph_osdmap_flag (struct ceph_osd_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_test_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_each_request (struct ceph_osd_client*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ have_pool_full (struct ceph_osd_client*) ; 

__attribute__((used)) static void ceph_osdc_abort_on_full(struct ceph_osd_client *osdc)
{
	bool victims = false;

	if (ceph_test_opt(osdc->client, ABORT_ON_FULL) &&
	    (ceph_osdmap_flag(osdc, CEPH_OSDMAP_FULL) || have_pool_full(osdc)))
		for_each_request(osdc, abort_on_full_fn, &victims);
}