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
typedef  int uint32_t ;
typedef  int ULONG ;

/* Variables and functions */
 int FILE_APPEND_DATA ; 
 int FILE_CREATE ; 
 int FILE_EXECUTE ; 
 int FILE_OPEN_IF ; 
 int FILE_OVERWRITE ; 
 int FILE_OVERWRITE_IF ; 
 int FILE_READ_DATA ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int FILE_SUPERSEDE ; 
 int FILE_WRITE_ATTRIBUTES ; 
 int FILE_WRITE_DATA ; 
 int OPEN4_SHARE_ACCESS_BOTH ; 
 int OPEN4_SHARE_ACCESS_READ ; 
 int OPEN4_SHARE_ACCESS_WANT_NO_DELEG ; 
 int OPEN4_SHARE_ACCESS_WRITE ; 
 int OPEN4_SHARE_DENY_BOTH ; 
 int OPEN4_SHARE_DENY_NONE ; 
 int OPEN4_SHARE_DENY_READ ; 
 int OPEN4_SHARE_DENY_WRITE ; 

__attribute__((used)) static void map_access_2_allowdeny(ULONG access_mask, ULONG access_mode,
                                   ULONG disposition, uint32_t *allow, uint32_t *deny)
{
    if ((access_mask & 
            (FILE_WRITE_DATA | FILE_APPEND_DATA | FILE_WRITE_ATTRIBUTES)) &&
            (access_mask & (FILE_READ_DATA | FILE_EXECUTE)))
        *allow = OPEN4_SHARE_ACCESS_BOTH;
    else if (access_mask & (FILE_READ_DATA | FILE_EXECUTE))
        *allow = OPEN4_SHARE_ACCESS_READ;
    else if (access_mask & 
                (FILE_WRITE_DATA | FILE_APPEND_DATA | FILE_WRITE_ATTRIBUTES))
        *allow = OPEN4_SHARE_ACCESS_WRITE;
    /* if we are creating a file and no data access is specified, then 
     * do an open and request no delegations. example open with share access 0
     * and share deny 0 (ie deny_both).
     */
    if ((disposition == FILE_CREATE || disposition == FILE_OPEN_IF || 
            disposition == FILE_OVERWRITE_IF || disposition == FILE_SUPERSEDE ||
            disposition == FILE_OVERWRITE) &&
            !(access_mask & (FILE_WRITE_DATA | FILE_APPEND_DATA | 
            FILE_WRITE_ATTRIBUTES | FILE_READ_DATA | FILE_EXECUTE)))
        *allow = OPEN4_SHARE_ACCESS_READ | OPEN4_SHARE_ACCESS_WANT_NO_DELEG;

#define FIX_ALLOW_DENY_WIN2NFS_CONVERSION
#ifdef FIX_ALLOW_DENY_WIN2NFS_CONVERSION
    if ((access_mode & FILE_SHARE_READ) &&
            (access_mode & FILE_SHARE_WRITE))
        *deny = OPEN4_SHARE_DENY_NONE;
    else if (access_mode & FILE_SHARE_READ)
        *deny = OPEN4_SHARE_DENY_WRITE;
    else if (access_mode & FILE_SHARE_WRITE)
        *deny = OPEN4_SHARE_DENY_READ;
    else
        *deny = OPEN4_SHARE_DENY_BOTH;
#else
    // AGLO: 11/13/2009.
    // readonly file that is being opened for reading with a
    // share read mode given above logic translates into deny
    // write and linux server does not allow it.
    *deny = OPEN4_SHARE_DENY_NONE;
#endif
}