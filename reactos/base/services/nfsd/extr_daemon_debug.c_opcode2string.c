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
typedef  int DWORD ;

/* Variables and functions */
#define  NFS41_ACL_QUERY 145 
#define  NFS41_ACL_SET 144 
#define  NFS41_CLOSE 143 
#define  NFS41_DIR_QUERY 142 
#define  NFS41_EA_GET 141 
#define  NFS41_EA_SET 140 
#define  NFS41_FILE_QUERY 139 
#define  NFS41_FILE_SET 138 
#define  NFS41_LOCK 137 
#define  NFS41_MOUNT 136 
#define  NFS41_OPEN 135 
#define  NFS41_READ 134 
#define  NFS41_SHUTDOWN 133 
#define  NFS41_SYMLINK 132 
#define  NFS41_UNLOCK 131 
#define  NFS41_UNMOUNT 130 
#define  NFS41_VOLUME_QUERY 129 
#define  NFS41_WRITE 128 

const char* opcode2string(DWORD opcode)
{
    switch(opcode) {
    case NFS41_SHUTDOWN:    return "NFS41_SHUTDOWN";
    case NFS41_MOUNT:       return "NFS41_MOUNT";
    case NFS41_UNMOUNT:     return "NFS41_UNMOUNT";
    case NFS41_OPEN:        return "NFS41_OPEN";
    case NFS41_CLOSE:       return "NFS41_CLOSE";
    case NFS41_READ:        return "NFS41_READ";
    case NFS41_WRITE:       return "NFS41_WRITE";
    case NFS41_LOCK:        return "NFS41_LOCK";
    case NFS41_UNLOCK:      return "NFS41_UNLOCK";
    case NFS41_DIR_QUERY:   return "NFS41_DIR_QUERY";
    case NFS41_FILE_QUERY:  return "NFS41_FILE_QUERY";
    case NFS41_FILE_SET:    return "NFS41_FILE_SET";
    case NFS41_EA_SET:      return "NFS41_EA_SET";
    case NFS41_EA_GET:      return "NFS41_EA_GET";
    case NFS41_SYMLINK:     return "NFS41_SYMLINK";
    case NFS41_VOLUME_QUERY: return "NFS41_VOLUME_QUERY";
    case NFS41_ACL_QUERY:   return "NFS41_ACL_QUERY";
    case NFS41_ACL_SET:     return "NFS41_ACL_SET";
    default:                return "UNKNOWN";
    }
}