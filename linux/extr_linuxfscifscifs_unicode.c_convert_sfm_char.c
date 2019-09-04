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
typedef  int __u16 ;

/* Variables and functions */
#define  SFM_ASTERISK 136 
#define  SFM_COLON 135 
#define  SFM_DOUBLEQUOTE 134 
#define  SFM_GRTRTHAN 133 
#define  SFM_LESSTHAN 132 
#define  SFM_PERIOD 131 
#define  SFM_PIPE 130 
#define  SFM_QUESTION 129 
#define  SFM_SPACE 128 

__attribute__((used)) static bool
convert_sfm_char(const __u16 src_char, char *target)
{
	if (src_char >= 0xF001 && src_char <= 0xF01F) {
		*target = src_char - 0xF000;
		return true;
	}
	switch (src_char) {
	case SFM_COLON:
		*target = ':';
		break;
	case SFM_DOUBLEQUOTE:
		*target = '"';
		break;
	case SFM_ASTERISK:
		*target = '*';
		break;
	case SFM_QUESTION:
		*target = '?';
		break;
	case SFM_PIPE:
		*target = '|';
		break;
	case SFM_GRTRTHAN:
		*target = '>';
		break;
	case SFM_LESSTHAN:
		*target = '<';
		break;
	case SFM_SPACE:
		*target = ' ';
		break;
	case SFM_PERIOD:
		*target = '.';
		break;
	default:
		return false;
	}
	return true;
}