#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ dwFileAttributes; } ;
typedef  TYPE_1__ ngx_file_info_t ;

/* Variables and functions */
 scalar_t__ GetFileAttributes (char*) ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 

int ngx_file_type(char *file, ngx_file_info_t *sb)
{
    sb->dwFileAttributes = GetFileAttributes(file);

    if (sb->dwFileAttributes == INVALID_FILE_ATTRIBUTES) {
        return -1;
    }

    return 0;
}