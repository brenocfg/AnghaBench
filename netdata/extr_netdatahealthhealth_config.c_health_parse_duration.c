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
typedef  int calculated_number ;

/* Variables and functions */
 scalar_t__ isdigit (char) ; 
 int str2ld (char*,char**) ; 

__attribute__((used)) static inline int health_parse_duration(char *string, int *result) {
    // make sure it is a number
    if(!*string || !(isdigit(*string) || *string == '+' || *string == '-')) {
        *result = 0;
        return 0;
    }

    char *e = NULL;
    calculated_number n = str2ld(string, &e);
    if(e && *e) {
        switch (*e) {
            case 'Y':
                *result = (int) (n * 86400 * 365);
                break;
            case 'M':
                *result = (int) (n * 86400 * 30);
                break;
            case 'w':
                *result = (int) (n * 86400 * 7);
                break;
            case 'd':
                *result = (int) (n * 86400);
                break;
            case 'h':
                *result = (int) (n * 3600);
                break;
            case 'm':
                *result = (int) (n * 60);
                break;

            default:
            case 's':
                *result = (int) (n);
                break;
        }
    }
    else
        *result = (int)(n);

    return 1;
}