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
typedef  int zend_off_t ;

/* Variables and functions */
 scalar_t__ isIDSeparator (char) ; 

__attribute__((used)) static zend_off_t getStrrtokenPos(char* str, zend_off_t savedPos)
{
	zend_off_t result =-1;
	zend_off_t i;

	for(i=savedPos-1; i>=0; i--) {
		if(isIDSeparator(*(str+i)) ){
			/* delimiter found; check for singleton */
			if(i>=2 && isIDSeparator(*(str+i-2)) ){
				/* a singleton; so send the position of token before the singleton */
				result = i-2;
			} else {
				result = i;
			}
			break;
		}
	}
	if(result < 1){
		/* Just in case inavlid locale e.g. '-x-xyz' or '-sl_Latn' */
		result =-1;
	}
	return result;
}