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
typedef  enum pnfs_iomode { ____Placeholder_pnfs_iomode } pnfs_iomode ;

/* Variables and functions */
#define  PNFS_IOMODE_ANY 130 
#define  PNFS_IOMODE_READ 129 
#define  PNFS_IOMODE_RW 128 

const char* pnfs_iomode_string(enum pnfs_iomode iomode)
{
    switch (iomode) {
    case PNFS_IOMODE_READ:      return "PNFS_IOMODE_READ";
    case PNFS_IOMODE_RW:        return "PNFS_IOMODE_RW";
    case PNFS_IOMODE_ANY:       return "PNFS_IOMODE_ANY";
    default:                    return "Invalid io mode";
    }
}