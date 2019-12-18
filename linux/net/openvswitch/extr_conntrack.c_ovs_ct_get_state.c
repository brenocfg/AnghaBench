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
typedef  int /*<<< orphan*/  u8 ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
#define  IP_CT_ESTABLISHED 132 
#define  IP_CT_ESTABLISHED_REPLY 131 
#define  IP_CT_NEW 130 
#define  IP_CT_RELATED 129 
#define  IP_CT_RELATED_REPLY 128 
 int /*<<< orphan*/  OVS_CS_F_ESTABLISHED ; 
 int /*<<< orphan*/  OVS_CS_F_NEW ; 
 int /*<<< orphan*/  OVS_CS_F_RELATED ; 
 int /*<<< orphan*/  OVS_CS_F_REPLY_DIR ; 
 int /*<<< orphan*/  OVS_CS_F_TRACKED ; 

__attribute__((used)) static u8 ovs_ct_get_state(enum ip_conntrack_info ctinfo)
{
	u8 ct_state = OVS_CS_F_TRACKED;

	switch (ctinfo) {
	case IP_CT_ESTABLISHED_REPLY:
	case IP_CT_RELATED_REPLY:
		ct_state |= OVS_CS_F_REPLY_DIR;
		break;
	default:
		break;
	}

	switch (ctinfo) {
	case IP_CT_ESTABLISHED:
	case IP_CT_ESTABLISHED_REPLY:
		ct_state |= OVS_CS_F_ESTABLISHED;
		break;
	case IP_CT_RELATED:
	case IP_CT_RELATED_REPLY:
		ct_state |= OVS_CS_F_RELATED;
		break;
	case IP_CT_NEW:
		ct_state |= OVS_CS_F_NEW;
		break;
	default:
		break;
	}

	return ct_state;
}