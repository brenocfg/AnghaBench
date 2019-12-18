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
typedef  int INT ;
typedef  int DWORD ;

/* Variables and functions */

__attribute__((used)) static INT find_file_extension(const WCHAR *path, DWORD path_len) {
    const WCHAR *end;

    for(end = path+path_len-1; end >= path && *end != '/' && *end != '\\'; --end) {
        if(*end == '.')
            return end-path;
    }

    return -1;
}