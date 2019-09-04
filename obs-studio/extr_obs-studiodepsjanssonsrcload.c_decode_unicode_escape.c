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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ l_isdigit (char) ; 
 scalar_t__ l_islower (char) ; 
 scalar_t__ l_isupper (char) ; 

__attribute__((used)) static int32_t decode_unicode_escape(const char *str)
{
    int i;
    int32_t value = 0;

    assert(str[0] == 'u');

    for(i = 1; i <= 4; i++) {
        char c = str[i];
        value <<= 4;
        if(l_isdigit(c))
            value += c - '0';
        else if(l_islower(c))
            value += c - 'a' + 10;
        else if(l_isupper(c))
            value += c - 'A' + 10;
        else
            return -1;
    }

    return value;
}