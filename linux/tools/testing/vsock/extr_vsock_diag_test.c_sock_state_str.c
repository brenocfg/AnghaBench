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
#define  TCP_CLOSE 132 
#define  TCP_CLOSING 131 
#define  TCP_ESTABLISHED 130 
#define  TCP_LISTEN 129 
#define  TCP_SYN_SENT 128 

__attribute__((used)) static const char *sock_state_str(int state)
{
	switch (state) {
	case TCP_CLOSE:
		return "UNCONNECTED";
	case TCP_SYN_SENT:
		return "CONNECTING";
	case TCP_ESTABLISHED:
		return "CONNECTED";
	case TCP_CLOSING:
		return "DISCONNECTING";
	case TCP_LISTEN:
		return "LISTEN";
	default:
		return "INVALID STATE";
	}
}