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
typedef  int u16 ;

/* Variables and functions */
#define  PID_IPCP 130 
#define  PID_IPV6CP 129 
#define  PID_LCP 128 

__attribute__((used)) static inline const char* proto_name(u16 pid)
{
	switch (pid) {
	case PID_LCP:
		return "LCP";
	case PID_IPCP:
		return "IPCP";
	case PID_IPV6CP:
		return "IPV6CP";
	default:
		return NULL;
	}
}