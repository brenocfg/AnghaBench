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
 scalar_t__ isdigit (char const) ; 
 scalar_t__ isspace (char const) ; 
 int str2ld (char const*,char**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 scalar_t__ unlikely (int) ; 

int config_parse_duration(const char* string, int* result) {
    while(*string && isspace(*string)) string++;

    if(unlikely(!*string)) goto fallback;

    if(*string == 'n' && !strcmp(string, "never")) {
        // this is a valid option
        *result = 0;
        return 1;
    }

    // make sure it is a number
    if(!(isdigit(*string) || *string == '+' || *string == '-')) goto fallback;

    char *e = NULL;
    calculated_number n = str2ld(string, &e);
    if(e && *e) {
        switch (*e) {
            case 'Y':
                *result = (int) (n * 31536000);
                break;
            case 'M':
                *result = (int) (n * 2592000);
                break;
            case 'w':
                *result = (int) (n * 604800);
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
            case 's':
            default:
                *result = (int) (n);
                break;
        }
    }
    else
        *result = (int)(n);

    return 1;

    fallback:
    *result = 0;
    return 0;
}