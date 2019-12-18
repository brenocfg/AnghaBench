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
 int /*<<< orphan*/  memcmp (char const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

char* strnstr(const char* string1, const char* string2, size_t len)
{
    size_t length2;

    length2 = strlen(string2);
    if (!length2) {
        return (char*)string1;
    }

    while (len >= length2) {
        len--;
        if (!memcmp(string1, string2, length2))
            return (char*)string1;
        string1++;
    }
    return NULL;
}