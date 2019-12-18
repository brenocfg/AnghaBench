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

int
PrintNum(char * buf, unsigned long u, int base, int negFlag, 
	 int length, int ladjust, char padc, int upcase)
{
    /* algorithm :
     *  1. prints the number from left to right in reverse form.
     *  2. fill the remaining spaces with padc if length is longer than
     *     the actual length
     *     TRICKY : if left adjusted, no "0" padding.
     *		    if negtive, insert  "0" padding between "0" and number.
     *  3. if (!ladjust) we reverse the whole string including paddings
     *  4. otherwise we only reverse the actual string representing the num.
     */

    int actualLength =0;
    char *p = buf;
    int i;

    do {
	int tmp = u %base;
	if (tmp <= 9) {
	    *p++ = '0' + tmp;
	} else if (upcase) {
	    *p++ = 'A' + tmp - 10;
	} else {
	    *p++ = 'a' + tmp - 10;
	}
	u /= base;
    } while (u != 0);

    if (negFlag) {
	*p++ = '-';
    }

    /* figure out actual length and adjust the maximum length */
    actualLength = p - buf;
    if (length < actualLength) length = actualLength;

    /* add padding */
    if (ladjust) {
	padc = ' ';
    }
    if (negFlag && !ladjust && (padc == '0')) {
	for (i = actualLength-1; i< length-1; i++) buf[i] = padc;
	buf[length -1] = '-';
    } else {
	for (i = actualLength; i< length; i++) buf[i] = padc;
    }
	    

    /* prepare to reverse the string */
    {
	int begin = 0;
	int end;
	if (ladjust) {
	    end = actualLength - 1;
	} else {
	    end = length -1;
	}

	while (end > begin) {
	    char tmp = buf[begin];
	    buf[begin] = buf[end];
	    buf[end] = tmp;
	    begin ++;
	    end --;
	}
    }

    /* adjust the string pointer */
    return length;
}