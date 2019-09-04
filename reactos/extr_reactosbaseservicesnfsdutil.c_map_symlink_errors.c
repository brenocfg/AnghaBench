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
 int ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  ERROR_BAD_NET_RESP ; 
 int ERROR_INVALID_REPARSE_DATA ; 
 int ERROR_NOT_A_REPARSE_POINT ; 
 int ERROR_NOT_EMPTY ; 
#define  NFS4ERR_ACCESS 132 
#define  NFS4ERR_BADCHAR 131 
#define  NFS4ERR_BADNAME 130 
#define  NFS4ERR_NOTEMPTY 129 
#define  NFS4ERR_WRONG_TYPE 128 
 int nfs_to_windows_error (int,int /*<<< orphan*/ ) ; 

int map_symlink_errors(int status)
{
    switch (status) {
    case NFS4ERR_BADCHAR:
    case NFS4ERR_BADNAME:       return ERROR_INVALID_REPARSE_DATA;
    case NFS4ERR_WRONG_TYPE:    return ERROR_NOT_A_REPARSE_POINT;
    case NFS4ERR_ACCESS:        return ERROR_ACCESS_DENIED;
    case NFS4ERR_NOTEMPTY:      return ERROR_NOT_EMPTY;
    default: return nfs_to_windows_error(status, ERROR_BAD_NET_RESP);
    }
}