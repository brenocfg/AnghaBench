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
struct t3cdev {struct cxgbi_ppm* ulp_iscsi; } ;
struct cxgbi_ppm {int dummy; } ;
struct cxgbi_device {scalar_t__ lldev; } ;

/* Variables and functions */

__attribute__((used)) static struct cxgbi_ppm *cdev2ppm(struct cxgbi_device *cdev)
{
	return ((struct t3cdev *)cdev->lldev)->ulp_iscsi;
}