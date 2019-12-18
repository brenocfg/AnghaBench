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
typedef  enum pnfs_layout_type { ____Placeholder_pnfs_layout_type } pnfs_layout_type ;

/* Variables and functions */
#define  PNFS_LAYOUTTYPE_BLOCK 130 
#define  PNFS_LAYOUTTYPE_FILE 129 
#define  PNFS_LAYOUTTYPE_OBJECT 128 

const char* pnfs_layout_type_string(enum pnfs_layout_type type)
{
    switch (type) {
    case PNFS_LAYOUTTYPE_FILE:  return "PNFS_LAYOUTTYPE_FILE";
    case PNFS_LAYOUTTYPE_OBJECT: return "PNFS_LAYOUTTYPE_OBJECT";
    case PNFS_LAYOUTTYPE_BLOCK: return "PNFS_LAYOUTTYPE_BLOCK";
    default:                    return "Invalid layout type";
    }
}