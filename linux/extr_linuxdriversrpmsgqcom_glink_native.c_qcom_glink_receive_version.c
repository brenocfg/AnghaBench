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
typedef  int u32 ;
struct qcom_glink {int features; } ;

/* Variables and functions */
#define  GLINK_VERSION_1 128 
 int /*<<< orphan*/  qcom_glink_send_version_ack (struct qcom_glink*) ; 

__attribute__((used)) static void qcom_glink_receive_version(struct qcom_glink *glink,
				       u32 version,
				       u32 features)
{
	switch (version) {
	case 0:
		break;
	case GLINK_VERSION_1:
		glink->features &= features;
		/* FALLTHROUGH */
	default:
		qcom_glink_send_version_ack(glink);
		break;
	}
}