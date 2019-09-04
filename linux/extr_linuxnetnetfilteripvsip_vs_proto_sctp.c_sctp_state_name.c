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
 int IP_VS_SCTP_S_LAST ; 
 char const** sctp_state_name_table ; 

__attribute__((used)) static const char *sctp_state_name(int state)
{
	if (state >= IP_VS_SCTP_S_LAST)
		return "ERR!";
	if (sctp_state_name_table[state])
		return sctp_state_name_table[state];
	return "?";
}