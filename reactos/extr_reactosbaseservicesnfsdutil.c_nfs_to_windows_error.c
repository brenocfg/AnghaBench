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
 int ERROR_ATOMIC_LOCKS_NOT_SUPPORTED ; 
 int ERROR_BUFFER_OVERFLOW ; 
 int ERROR_DISK_FULL ; 
 int ERROR_FILENAME_EXCED_RANGE ; 
 int ERROR_FILE_EXISTS ; 
 int ERROR_FILE_INVALID ; 
 int ERROR_FILE_NOT_FOUND ; 
 int ERROR_FILE_TOO_LARGE ; 
 int ERROR_INVALID_NAME ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_LOCK_FAILED ; 
 int ERROR_LOCK_VIOLATION ; 
 int ERROR_NETNAME_DELETED ; 
 int ERROR_NETWORK_ACCESS_DENIED ; 
 int ERROR_NET_WRITE_FAULT ; 
 int ERROR_NOT_EMPTY ; 
 int ERROR_NOT_LOCKED ; 
 int ERROR_NOT_SAME_DEVICE ; 
 int ERROR_NOT_SUPPORTED ; 
 int ERROR_SHARING_VIOLATION ; 
 int ERROR_TOO_MANY_LINKS ; 
#define  NFS4ERR_ACCESS 162 
#define  NFS4ERR_ADMIN_REVOKED 161 
#define  NFS4ERR_ATTRNOTSUPP 160 
#define  NFS4ERR_BADCHAR 159 
#define  NFS4ERR_BADNAME 158 
#define  NFS4ERR_BAD_STATEID 157 
#define  NFS4ERR_DENIED 156 
#define  NFS4ERR_EXIST 155 
#define  NFS4ERR_EXPIRED 154 
#define  NFS4ERR_FBIG 153 
#define  NFS4ERR_INVAL 152 
#define  NFS4ERR_IO 151 
#define  NFS4ERR_ISDIR 150 
#define  NFS4ERR_LOCKED 149 
#define  NFS4ERR_LOCK_NOTSUPP 148 
#define  NFS4ERR_LOCK_RANGE 147 
#define  NFS4ERR_MLINK 146 
#define  NFS4ERR_NAMETOOLONG 145 
#define  NFS4ERR_NOENT 144 
#define  NFS4ERR_NOFILEHANDLE 143 
#define  NFS4ERR_NOSPC 142 
#define  NFS4ERR_NOTDIR 141 
#define  NFS4ERR_NOTEMPTY 140 
#define  NFS4ERR_OLD_STATEID 139 
#define  NFS4ERR_OPENMODE 138 
#define  NFS4ERR_PERM 137 
#define  NFS4ERR_ROFS 136 
#define  NFS4ERR_SHARE_DENIED 135 
#define  NFS4ERR_STALE 134 
#define  NFS4ERR_SYMLINK 133 
#define  NFS4ERR_TOOSMALL 132 
#define  NFS4ERR_WRONGSEC 131 
#define  NFS4ERR_WRONG_TYPE 130 
#define  NFS4ERR_XDEV 129 
#define  NFS4_OK 128 
 int NO_ERROR ; 
 int /*<<< orphan*/  dprintf (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  eprintf (char*,int) ; 
 int /*<<< orphan*/  nfs_error_string (int) ; 

int nfs_to_windows_error(int status, int default_error)
{
    /* make sure this is actually an nfs error */
    if (status < 0 || (status > 70 && status < 10001) || status > 10087) {
        eprintf("nfs_to_windows_error called with non-nfs "
            "error code %d; returning the error as is\n", status);
        return status;
    }

    switch (status) {
    case NFS4_OK:               return NO_ERROR;
    case NFS4ERR_PERM:          return ERROR_ACCESS_DENIED;
    case NFS4ERR_NOENT:         return ERROR_FILE_NOT_FOUND;
    case NFS4ERR_IO:            return ERROR_NET_WRITE_FAULT;
    case NFS4ERR_ACCESS:        return ERROR_ACCESS_DENIED;
    case NFS4ERR_EXIST:         return ERROR_FILE_EXISTS;
    case NFS4ERR_XDEV:          return ERROR_NOT_SAME_DEVICE;
    case NFS4ERR_INVAL:         return ERROR_INVALID_PARAMETER;
    case NFS4ERR_FBIG:          return ERROR_FILE_TOO_LARGE;
    case NFS4ERR_NOSPC:         return ERROR_DISK_FULL;
    case NFS4ERR_ROFS:          return ERROR_NETWORK_ACCESS_DENIED;
    case NFS4ERR_MLINK:         return ERROR_TOO_MANY_LINKS;
    case NFS4ERR_NAMETOOLONG:   return ERROR_FILENAME_EXCED_RANGE;
    case NFS4ERR_STALE:         return ERROR_NETNAME_DELETED;
    case NFS4ERR_NOTEMPTY:      return ERROR_NOT_EMPTY;
    case NFS4ERR_DENIED:        return ERROR_LOCK_FAILED;
    case NFS4ERR_TOOSMALL:      return ERROR_BUFFER_OVERFLOW;
    case NFS4ERR_LOCKED:        return ERROR_LOCK_VIOLATION;
    case NFS4ERR_SHARE_DENIED:  return ERROR_SHARING_VIOLATION;
    case NFS4ERR_LOCK_RANGE:    return ERROR_NOT_LOCKED;
    case NFS4ERR_ATTRNOTSUPP:   return ERROR_NOT_SUPPORTED;
    case NFS4ERR_OPENMODE:      return ERROR_ACCESS_DENIED;
    case NFS4ERR_LOCK_NOTSUPP:  return ERROR_ATOMIC_LOCKS_NOT_SUPPORTED;

    case NFS4ERR_BADCHAR:
    case NFS4ERR_BADNAME:       return ERROR_INVALID_NAME;

    case NFS4ERR_NOTDIR:
    case NFS4ERR_ISDIR:
    case NFS4ERR_SYMLINK:
    case NFS4ERR_WRONG_TYPE:    return ERROR_INVALID_PARAMETER;

    case NFS4ERR_EXPIRED:
    case NFS4ERR_NOFILEHANDLE:
    case NFS4ERR_OLD_STATEID:
    case NFS4ERR_BAD_STATEID:
    case NFS4ERR_ADMIN_REVOKED: return ERROR_FILE_INVALID;

    case NFS4ERR_WRONGSEC:      return ERROR_ACCESS_DENIED;

    default:
        dprintf(1, "nfs error %s not mapped to windows error; "
            "returning default error %d\n",
            nfs_error_string(status), default_error);
        return default_error;
    }
}