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
struct msg_msg {long m_type; } ;

/* Variables and functions */
#define  SEARCH_ANY 132 
#define  SEARCH_EQUAL 131 
#define  SEARCH_LESSEQUAL 130 
#define  SEARCH_NOTEQUAL 129 
#define  SEARCH_NUMBER 128 

__attribute__((used)) static int testmsg(struct msg_msg *msg, long type, int mode)
{
	switch (mode) {
	case SEARCH_ANY:
	case SEARCH_NUMBER:
		return 1;
	case SEARCH_LESSEQUAL:
		if (msg->m_type <= type)
			return 1;
		break;
	case SEARCH_EQUAL:
		if (msg->m_type == type)
			return 1;
		break;
	case SEARCH_NOTEQUAL:
		if (msg->m_type != type)
			return 1;
		break;
	}
	return 0;
}