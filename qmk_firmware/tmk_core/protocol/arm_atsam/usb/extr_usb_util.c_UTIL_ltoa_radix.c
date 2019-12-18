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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 char digit (int,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

int UTIL_ltoa_radix(int64_t value, char *dest, int radix) {
    int64_t original = value;  // save original value
    char    buf[25]  = "";
    int     c        = sizeof(buf) - 1;
    int     last     = c;
    int     d;
    int     size;

    if (value < 0)  // if it's negative, take the absolute value
        value = -value;

    do  // write least significant digit of value that's left
    {
        d        = (value % radix);
        buf[--c] = digit(d, radix);
        value /= radix;
    } while (value);

    if (original < 0) buf[--c] = '-';

    size = last - c + 1;  // includes null at end
    memcpy(dest, &buf[c], last - c + 1);

    return (size - 1);  // without null termination
}