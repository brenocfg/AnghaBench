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
typedef  int zend_uchar ;
typedef  char const* start ;

/* Variables and functions */
 scalar_t__ valid_ujis (char const) ; 
 scalar_t__ valid_ujis_kata (char const) ; 
 scalar_t__ valid_ujis_ss2 (char const) ; 
 scalar_t__ valid_ujis_ss3 (char const) ; 

__attribute__((used)) static unsigned int check_mb_ujis(const char * const start, const char * const end)
{
	if (*(zend_uchar*)start < 0x80) {
		return 0;	/* invalid ujis character */
	}
	if (valid_ujis(*(start)) && valid_ujis(*((start)+1))) {
		return 2;
	}
	if (valid_ujis_ss2(*(start)) && valid_ujis_kata(*((start)+1))) {
		return 2;
	}
	if (valid_ujis_ss3(*(start)) && (end-start) > 2 && valid_ujis(*((start)+1)) && valid_ujis(*((start)+2))) {
		return 3;
	}
	return 0;
}