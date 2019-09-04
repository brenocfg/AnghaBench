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
typedef  int ACCESS_MASK ;

/* Variables and functions */
 int ACCESS_SYSTEM_SECURITY ; 
 int DELETE ; 
 int FILE_ADD_FILE ; 
 int FILE_ADD_SUBDIRECTORY ; 
 int FILE_ALL_ACCESS ; 
 int FILE_APPEND_DATA ; 
 int FILE_CREATE_PIPE_INSTANCE ; 
 int FILE_DELETE_CHILD ; 
 int FILE_EXECUTE ; 
 int FILE_GENERIC_EXECUTE ; 
 int FILE_GENERIC_READ ; 
 int FILE_GENERIC_WRITE ; 
 int FILE_LIST_DIRECTORY ; 
 int FILE_READ_ATTRIBUTES ; 
 int FILE_READ_DATA ; 
 int FILE_READ_EA ; 
 int FILE_TRAVERSE ; 
 int FILE_WRITE_ATTRIBUTES ; 
 int FILE_WRITE_DATA ; 
 int FILE_WRITE_EA ; 
 int GENERIC_ALL ; 
 int GENERIC_EXECUTE ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 int MAXIMUM_ALLOWED ; 
 int READ_CONTROL ; 
 int SPECIFIC_RIGHTS_ALL ; 
 int STANDARD_RIGHTS_ALL ; 
 int STANDARD_RIGHTS_REQUIRED ; 
 int SYNCHRONIZE ; 
 int WRITE_DAC ; 
 int WRITE_OWNER ; 
 int /*<<< orphan*/  dprintf (int,char*,...) ; 

void print_windows_access_mask(int on, ACCESS_MASK m)
{
    if (!on) return;
    dprintf(1, "--> print_windows_access_mask: %x\n", m);
    if (m & GENERIC_READ)
        dprintf(1, "\tGENERIC_READ\n");
    if (m & GENERIC_WRITE)
        dprintf(1, "\tGENERIC_WRITE\n");
    if (m & GENERIC_EXECUTE)
        dprintf(1, "\tGENERIC_EXECUTE\n");
    if (m & GENERIC_ALL)
        dprintf(1, "\tGENERIC_ALL\n");
    if (m & MAXIMUM_ALLOWED)
        dprintf(1, "\tMAXIMUM_ALLOWED\n");
    if (m & ACCESS_SYSTEM_SECURITY)
        dprintf(1, "\tACCESS_SYSTEM_SECURITY\n");
    if ((m & SPECIFIC_RIGHTS_ALL) == SPECIFIC_RIGHTS_ALL)
        dprintf(1, "\tSPECIFIC_RIGHTS_ALL\n");
    if ((m & STANDARD_RIGHTS_ALL) == STANDARD_RIGHTS_ALL)
        dprintf(1, "\tSTANDARD_RIGHTS_ALL\n");
    if ((m & STANDARD_RIGHTS_REQUIRED) == STANDARD_RIGHTS_REQUIRED)
        dprintf(1, "\tSTANDARD_RIGHTS_REQUIRED\n");
    if (m & SYNCHRONIZE)
        dprintf(1, "\tSYNCHRONIZE\n");
    if (m & WRITE_OWNER)
        dprintf(1, "\tWRITE_OWNER\n");
    if (m & WRITE_DAC)
        dprintf(1, "\tWRITE_DAC\n");
    if (m & READ_CONTROL)
        dprintf(1, "\tREAD_CONTROL\n");
    if (m & DELETE)
        dprintf(1, "\tDELETE\n");
    if (m & FILE_READ_DATA)
        dprintf(1, "\tFILE_READ_DATA\n");
    if (m & FILE_LIST_DIRECTORY)
        dprintf(1, "\tFILE_LIST_DIRECTORY\n");
    if (m & FILE_WRITE_DATA)
        dprintf(1, "\tFILE_WRITE_DATA\n");
    if (m & FILE_ADD_FILE)
        dprintf(1, "\tFILE_ADD_FILE\n");
    if (m & FILE_APPEND_DATA)
        dprintf(1, "\tFILE_APPEND_DATA\n");
    if (m & FILE_ADD_SUBDIRECTORY)
        dprintf(1, "\tFILE_ADD_SUBDIRECTORY\n");
    if (m & FILE_CREATE_PIPE_INSTANCE)
        dprintf(1, "\tFILE_CREATE_PIPE_INSTANCE\n");
    if (m & FILE_READ_EA)
        dprintf(1, "\tFILE_READ_EA\n");
    if (m & FILE_WRITE_EA)
        dprintf(1, "\tFILE_WRITE_EA\n");
    if (m & FILE_EXECUTE)
        dprintf(1, "\tFILE_EXECUTE\n");
    if (m & FILE_TRAVERSE)
        dprintf(1, "\tFILE_TRAVERSE\n");
    if (m & FILE_DELETE_CHILD)
        dprintf(1, "\tFILE_DELETE_CHILD\n");
    if (m & FILE_READ_ATTRIBUTES)
        dprintf(1, "\tFILE_READ_ATTRIBUTES\n");
    if (m & FILE_WRITE_ATTRIBUTES)
        dprintf(1, "\tFILE_WRITE_ATTRIBUTES\n");
    if ((m & FILE_ALL_ACCESS) == FILE_ALL_ACCESS)
        dprintf(1, "\tFILE_ALL_ACCESS\n");
    if ((m & FILE_GENERIC_READ) == FILE_GENERIC_READ)
        dprintf(1, "\tFILE_GENERIC_READ\n");
    if ((m & FILE_GENERIC_WRITE) == FILE_GENERIC_WRITE)
        dprintf(1, "\tFILE_GENERIC_WRITE\n");
    if ((m & FILE_GENERIC_EXECUTE) == FILE_GENERIC_EXECUTE)
        dprintf(1, "\tFILE_GENERIC_EXECUTE\n");
}