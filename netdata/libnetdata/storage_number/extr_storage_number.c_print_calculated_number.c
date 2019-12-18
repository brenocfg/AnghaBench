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
typedef  unsigned long long calculated_number ;

/* Variables and functions */
 scalar_t__ calculated_number_llrint (unsigned long long) ; 
 double calculated_number_modf (unsigned long long,unsigned long long*) ; 
 scalar_t__ likely (int) ; 
 char* print_number_llu_r_smart (char*,unsigned long long) ; 
 scalar_t__ unlikely (int) ; 

int print_calculated_number(char *str, calculated_number value) {
    // info("printing number " CALCULATED_NUMBER_FORMAT, value);
    char integral_str[50], fractional_str[50];

    char *wstr = str;

    if(unlikely(value < 0)) {
        *wstr++ = '-';
        value = -value;
    }

    calculated_number integral, fractional;

#ifdef STORAGE_WITH_MATH
    fractional = calculated_number_modf(value, &integral) * 10000000.0;
#else
    fractional = ((unsigned long long)(value * 10000000ULL) % 10000000ULL);
#endif

    unsigned long long integral_int = (unsigned long long)integral;
    unsigned long long fractional_int = (unsigned long long)calculated_number_llrint(fractional);
    if(unlikely(fractional_int >= 10000000)) {
        integral_int += 1;
        fractional_int -= 10000000;
    }

    // info("integral " CALCULATED_NUMBER_FORMAT " (%llu), fractional " CALCULATED_NUMBER_FORMAT " (%llu)", integral, integral_int, fractional, fractional_int);

    char *istre;
    if(unlikely(integral_int == 0)) {
        integral_str[0] = '0';
        istre = &integral_str[1];
    }
    else
        // convert the integral part to string (reversed)
        istre = print_number_llu_r_smart(integral_str, integral_int);

    // copy reversed the integral string
    istre--;
    while( istre >= integral_str ) *wstr++ = *istre--;

    if(likely(fractional_int != 0)) {
        // add a dot
        *wstr++ = '.';

        // convert the fractional part to string (reversed)
        char *fstre = print_number_llu_r_smart(fractional_str, fractional_int);

        // prepend zeros to reach 7 digits length
        int decimal = 7;
        int len = (int)(fstre - fractional_str);
        while(len < decimal) {
            *wstr++ = '0';
            len++;
        }

        char *begin = fractional_str;
        while(begin < fstre && *begin == '0') begin++;

        // copy reversed the fractional string
        fstre--;
        while( fstre >= begin ) *wstr++ = *fstre--;
    }

    *wstr = '\0';
    // info("printed number '%s'", str);
    return (int)(wstr - str);
}