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
struct TYPE_2__ {scalar_t__* iscsi_ppm; } ;
struct cxgbit_device {TYPE_1__ lldi; } ;
struct cxgbi_ppm {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline
struct cxgbi_ppm *cdev2ppm(struct cxgbit_device *cdev)
{
	return (struct cxgbi_ppm *)(*cdev->lldi.iscsi_ppm);
}