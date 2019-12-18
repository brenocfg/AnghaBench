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
typedef  char* LPWSTR ;

/* Variables and functions */
 int lstrlenW (char*) ; 
 char* strchrW (char*,char) ; 
 char* strdupW (char*) ; 

__attribute__((used)) static LPWSTR get_ini_field(LPWSTR buf, int field)
{
    LPWSTR beg, end;
    int i = 1;

    if (field == 0)
        return strdupW(buf);

    beg = buf;
    while ((end = strchrW(beg, ',')) && i < field)
    {
        beg = end + 1;
        while (*beg == ' ')
            beg++;

        i++;
    }

    end = strchrW(beg, ',');
    if (!end)
        end = beg + lstrlenW(beg);

    *end = '\0';
    return strdupW(beg);
}