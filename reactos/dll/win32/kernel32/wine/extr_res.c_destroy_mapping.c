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
struct mapping_info {scalar_t__ file; } ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mapping_info*) ; 
 int /*<<< orphan*/  unmap_file_from_memory (struct mapping_info*) ; 

__attribute__((used)) static void destroy_mapping( struct mapping_info *mi )
{
    if (!mi)
        return;
    unmap_file_from_memory( mi );
    if (mi->file)
        CloseHandle( mi->file );
    HeapFree( GetProcessHeap(), 0, mi );
}