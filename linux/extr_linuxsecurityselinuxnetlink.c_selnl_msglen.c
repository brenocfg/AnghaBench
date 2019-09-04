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
struct selnl_msg_setenforce {int dummy; } ;
struct selnl_msg_policyload {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  SELNL_MSG_POLICYLOAD 129 
#define  SELNL_MSG_SETENFORCE 128 

__attribute__((used)) static int selnl_msglen(int msgtype)
{
	int ret = 0;

	switch (msgtype) {
	case SELNL_MSG_SETENFORCE:
		ret = sizeof(struct selnl_msg_setenforce);
		break;

	case SELNL_MSG_POLICYLOAD:
		ret = sizeof(struct selnl_msg_policyload);
		break;

	default:
		BUG();
	}
	return ret;
}