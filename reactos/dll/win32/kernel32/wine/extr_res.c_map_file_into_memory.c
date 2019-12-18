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
struct mapping_info {int /*<<< orphan*/ * base; int /*<<< orphan*/  size; int /*<<< orphan*/  file; scalar_t__ read_write; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateFileMappingW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_MAP_READ ; 
 int FILE_MAP_WRITE ; 
 int /*<<< orphan*/ * MapViewOfFile (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PAGE_READONLY ; 
 int PAGE_READWRITE ; 

__attribute__((used)) static BOOL map_file_into_memory( struct mapping_info *mi )
{
    DWORD page_attr, perm;
    HANDLE mapping;

    if (mi->read_write)
    {
        page_attr = PAGE_READWRITE;
        perm = FILE_MAP_WRITE | FILE_MAP_READ;
    }
    else
    {
        page_attr = PAGE_READONLY;
        perm = FILE_MAP_READ;
    }

    mapping = CreateFileMappingW( mi->file, NULL, page_attr, 0, 0, NULL );
    if (!mapping) return FALSE;

    mi->base = MapViewOfFile( mapping, perm, 0, 0, mi->size );
    CloseHandle( mapping );

    return mi->base != NULL;
}