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

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int EIO ; 
#define  MAIL_OUT_STATUS_COMPLETED 130 
#define  MAIL_OUT_STATUS_ERR_ACCESS 129 
#define  MAIL_OUT_STATUS_ERR_AUTH 128 
 int MAIL_OUT_STATUS_MASK ; 

__attribute__((used)) static int status_to_errno(u32 status)
{
	switch (status & MAIL_OUT_STATUS_MASK) {
	case MAIL_OUT_STATUS_COMPLETED:
		return 0;
	case MAIL_OUT_STATUS_ERR_AUTH:
		return -EINVAL;
	case MAIL_OUT_STATUS_ERR_ACCESS:
		return -EACCES;
	}

	return -EIO;
}