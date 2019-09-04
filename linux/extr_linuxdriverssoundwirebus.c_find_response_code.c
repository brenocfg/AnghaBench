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
typedef  enum sdw_command_response { ____Placeholder_sdw_command_response } sdw_command_response ;

/* Variables and functions */
 int EIO ; 
 int ENODATA ; 
 int ETIMEDOUT ; 
#define  SDW_CMD_IGNORED 130 
#define  SDW_CMD_OK 129 
#define  SDW_CMD_TIMEOUT 128 

__attribute__((used)) static inline int find_response_code(enum sdw_command_response resp)
{
	switch (resp) {
	case SDW_CMD_OK:
		return 0;

	case SDW_CMD_IGNORED:
		return -ENODATA;

	case SDW_CMD_TIMEOUT:
		return -ETIMEDOUT;

	default:
		return -EIO;
	}
}