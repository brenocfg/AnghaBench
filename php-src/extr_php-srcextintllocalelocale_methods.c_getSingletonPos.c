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
 scalar_t__ isIDSeparator (char const) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static zend_off_t getSingletonPos(const char* str)
{
	zend_off_t result =-1;
	size_t len = 0;

	if( str && ((len=strlen(str))>0) ){
		zend_off_t i = 0;
		for( i=0; (size_t)i < len ; i++){
			if( isIDSeparator(*(str+i)) ){
				if( i==1){
					/* string is of the form x-avy or a-prv1 */
					result =0;
					break;
				} else {
					/* delimiter found; check for singleton */
					if( isIDSeparator(*(str+i+2)) ){
						/* a singleton; so send the position of separator before singleton */
						result = i+1;
						break;
					}
				}
			}
		}/* end of for */

	}
	return result;
}