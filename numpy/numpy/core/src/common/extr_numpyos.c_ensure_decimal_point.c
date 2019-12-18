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
 int /*<<< orphan*/  Py_CHARMASK (char) ; 
 scalar_t__ isdigit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void
ensure_decimal_point(char* buffer, size_t buf_size)
{
    int insert_count = 0;
    char* chars_to_insert;

    /* search for the first non-digit character */
    char *p = buffer;
    if (*p == '-' || *p == '+')
        /*
         * Skip leading sign, if present.  I think this could only
         * ever be '-', but it can't hurt to check for both.
         */
        ++p;
    while (*p && isdigit(Py_CHARMASK(*p))) {
        ++p;
    }
    if (*p == '.') {
        if (isdigit(Py_CHARMASK(*(p+1)))) {
            /*
             * Nothing to do, we already have a decimal
             * point and a digit after it.
             */
        }
        else {
            /*
             * We have a decimal point, but no following
             * digit.  Insert a zero after the decimal.
             */
            ++p;
            chars_to_insert = "0";
            insert_count = 1;
        }
    }
    else {
        chars_to_insert = ".0";
        insert_count = 2;
    }
    if (insert_count) {
        size_t buf_len = strlen(buffer);
        if (buf_len + insert_count + 1 >= buf_size) {
            /*
             * If there is not enough room in the buffer
             * for the additional text, just skip it.  It's
             * not worth generating an error over.
             */
        }
        else {
            memmove(p + insert_count, p, buffer + strlen(buffer) - p + 1);
            memcpy(p, chars_to_insert, insert_count);
        }
    }
}