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
 long LONG_MAX ; 
 long LONG_MIN ; 
 int MSG_COPY ; 
 int MSG_EXCEPT ; 
 int SEARCH_ANY ; 
 int SEARCH_EQUAL ; 
 int SEARCH_LESSEQUAL ; 
 int SEARCH_NOTEQUAL ; 
 int SEARCH_NUMBER ; 

__attribute__((used)) static inline int convert_mode(long *msgtyp, int msgflg)
{
	if (msgflg & MSG_COPY)
		return SEARCH_NUMBER;
	/*
	 *  find message of correct type.
	 *  msgtyp = 0 => get first.
	 *  msgtyp > 0 => get first message of matching type.
	 *  msgtyp < 0 => get message with least type must be < abs(msgtype).
	 */
	if (*msgtyp == 0)
		return SEARCH_ANY;
	if (*msgtyp < 0) {
		if (*msgtyp == LONG_MIN) /* -LONG_MIN is undefined */
			*msgtyp = LONG_MAX;
		else
			*msgtyp = -*msgtyp;
		return SEARCH_LESSEQUAL;
	}
	if (msgflg & MSG_EXCEPT)
		return SEARCH_NOTEQUAL;
	return SEARCH_EQUAL;
}