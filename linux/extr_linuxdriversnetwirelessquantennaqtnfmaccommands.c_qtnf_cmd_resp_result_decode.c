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
typedef  enum qlink_cmd_result { ____Placeholder_qlink_cmd_result } qlink_cmd_result ;

/* Variables and functions */
 int EADDRINUSE ; 
 int EADDRNOTAVAIL ; 
 int EALREADY ; 
 int EFAULT ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOTSUPP ; 
#define  QLINK_CMD_RESULT_EADDRINUSE 134 
#define  QLINK_CMD_RESULT_EADDRNOTAVAIL 133 
#define  QLINK_CMD_RESULT_EALREADY 132 
#define  QLINK_CMD_RESULT_ENOTFOUND 131 
#define  QLINK_CMD_RESULT_ENOTSUPP 130 
#define  QLINK_CMD_RESULT_INVALID 129 
#define  QLINK_CMD_RESULT_OK 128 

__attribute__((used)) static int qtnf_cmd_resp_result_decode(enum qlink_cmd_result qcode)
{
	switch (qcode) {
	case QLINK_CMD_RESULT_OK:
		return 0;
	case QLINK_CMD_RESULT_INVALID:
		return -EINVAL;
	case QLINK_CMD_RESULT_ENOTSUPP:
		return -ENOTSUPP;
	case QLINK_CMD_RESULT_ENOTFOUND:
		return -ENOENT;
	case QLINK_CMD_RESULT_EALREADY:
		return -EALREADY;
	case QLINK_CMD_RESULT_EADDRINUSE:
		return -EADDRINUSE;
	case QLINK_CMD_RESULT_EADDRNOTAVAIL:
		return -EADDRNOTAVAIL;
	default:
		return -EFAULT;
	}
}