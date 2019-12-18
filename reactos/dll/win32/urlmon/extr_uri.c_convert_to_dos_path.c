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
typedef  char WCHAR ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ is_drive_path (char const*) ; 

__attribute__((used)) static void convert_to_dos_path(const WCHAR *path, DWORD path_len,
                                WCHAR *output, DWORD *output_len)
{
    const WCHAR *ptr = path;

    if(path_len > 3 && *ptr == '/' && is_drive_path(path+1))
        /* Skip over the leading / before the drive path. */
        ++ptr;

    for(; ptr < path+path_len; ++ptr) {
        if(*ptr == '/') {
            if(output)
                *output++ = '\\';
            (*output_len)++;
        } else {
            if(output)
                *output++ = *ptr;
            (*output_len)++;
        }
    }
}