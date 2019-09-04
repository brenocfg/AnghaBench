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
struct ceph_osd_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __submit_request (struct ceph_osd_request*,int) ; 
 int /*<<< orphan*/  account_request (struct ceph_osd_request*) ; 
 int /*<<< orphan*/  ceph_osdc_get_request (struct ceph_osd_request*) ; 

__attribute__((used)) static void submit_request(struct ceph_osd_request *req, bool wrlocked)
{
	ceph_osdc_get_request(req);
	account_request(req);
	__submit_request(req, wrlocked);
}