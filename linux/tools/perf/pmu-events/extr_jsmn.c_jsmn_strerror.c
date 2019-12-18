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
typedef  int jsmnerr_t ;

/* Variables and functions */
#define  JSMN_ERROR_INVAL 131 
#define  JSMN_ERROR_NOMEM 130 
#define  JSMN_ERROR_PART 129 
#define  JSMN_SUCCESS 128 

const char *jsmn_strerror(jsmnerr_t err)
{
	switch (err) {
	case JSMN_ERROR_NOMEM:
		return "No enough tokens";
	case JSMN_ERROR_INVAL:
		return "Invalid character inside JSON string";
	case JSMN_ERROR_PART:
		return "The string is not a full JSON packet, more bytes expected";
	case JSMN_SUCCESS:
		return "Success";
	default:
		return "Unknown json error";
	}
}