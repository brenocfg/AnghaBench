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
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int ERROR_FILESYSTEM_ABSENT ; 
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_PATH_NOT_FOUND ; 
 int ERROR_REPARSE ; 
#define  NFS4ERR_MOVED 130 
#define  NFS4ERR_NOENT 129 
#define  NFS4ERR_SYMLINK 128 
 int nfs_to_windows_error (int,int) ; 

__attribute__((used)) static int map_lookup_error(int status, bool_t last_component)
{
    switch (status) {
    case NFS4ERR_NOENT:
        if (last_component)     return ERROR_FILE_NOT_FOUND;
        else                    return ERROR_PATH_NOT_FOUND;
    case NFS4ERR_SYMLINK:       return ERROR_REPARSE;
    case NFS4ERR_MOVED:         return ERROR_FILESYSTEM_ABSENT;
    default: return nfs_to_windows_error(status, ERROR_FILE_NOT_FOUND);
    }
}