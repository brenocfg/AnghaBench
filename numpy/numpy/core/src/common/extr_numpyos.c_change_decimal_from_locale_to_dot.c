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
struct lconv {char* decimal_point; } ;

/* Variables and functions */
 int /*<<< orphan*/  Py_CHARMASK (char) ; 
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 struct lconv* localeconv () ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 

__attribute__((used)) static void
change_decimal_from_locale_to_dot(char* buffer)
{
    struct lconv *locale_data = localeconv();
    const char *decimal_point = locale_data->decimal_point;

    if (decimal_point[0] != '.' || decimal_point[1] != 0) {
        size_t decimal_point_len = strlen(decimal_point);

        if (*buffer == '+' || *buffer == '-') {
            buffer++;
        }
        while (isdigit(Py_CHARMASK(*buffer))) {
            buffer++;
        }
        if (strncmp(buffer, decimal_point, decimal_point_len) == 0) {
            *buffer = '.';
            buffer++;
            if (decimal_point_len > 1) {
                /* buffer needs to get smaller */
                size_t rest_len = strlen(buffer + (decimal_point_len - 1));
                memmove(buffer, buffer + (decimal_point_len - 1), rest_len);
                buffer[rest_len] = 0;
            }
        }
    }
}