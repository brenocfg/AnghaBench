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

/* Variables and functions */
#define  RTPROT_MROUTED 129 
#define  RTPROT_STATIC 128 

__attribute__((used)) static bool ipmr_rtm_validate_proto(unsigned char rtm_protocol)
{
	switch (rtm_protocol) {
	case RTPROT_STATIC:
	case RTPROT_MROUTED:
		return true;
	}
	return false;
}