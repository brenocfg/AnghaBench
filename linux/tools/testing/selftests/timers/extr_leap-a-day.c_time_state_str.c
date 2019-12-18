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
#define  TIME_BAD 133 
#define  TIME_DEL 132 
#define  TIME_INS 131 
#define  TIME_OK 130 
#define  TIME_OOP 129 
#define  TIME_WAIT 128 

char *time_state_str(int state)
{
	switch (state) {
	case TIME_OK:	return "TIME_OK";
	case TIME_INS:	return "TIME_INS";
	case TIME_DEL:	return "TIME_DEL";
	case TIME_OOP:	return "TIME_OOP";
	case TIME_WAIT:	return "TIME_WAIT";
	case TIME_BAD:	return "TIME_BAD";
	}
	return "ERROR";
}