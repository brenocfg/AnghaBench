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
 int /*<<< orphan*/  freez (char*) ; 
 scalar_t__ isalnum (char) ; 
 char* mallocz (int) ; 
 char* strdupz (char*) ; 
 int strlen (char*) ; 
 void* to_hex (char) ; 

char *url_encode(char *str) {
    char *buf, *pbuf;

    pbuf = buf = mallocz(strlen(str) * 3 + 1);

    while (*str) {
        if (isalnum(*str) || *str == '-' || *str == '_' || *str == '.' || *str == '~')
            *pbuf++ = *str;

        else if (*str == ' ')
            *pbuf++ = '+';

        else
            *pbuf++ = '%', *pbuf++ = to_hex(*str >> 4), *pbuf++ = to_hex(*str & 15);

        str++;
    }
    *pbuf = '\0';

    pbuf = strdupz(buf);
    freez(buf);
    return pbuf;
}