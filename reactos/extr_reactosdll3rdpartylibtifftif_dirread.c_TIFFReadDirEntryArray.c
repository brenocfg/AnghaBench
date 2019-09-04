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
typedef  int /*<<< orphan*/  uint64 ;
typedef  int /*<<< orphan*/  uint32 ;
typedef  enum TIFFReadDirEntryErr { ____Placeholder_TIFFReadDirEntryErr } TIFFReadDirEntryErr ;
typedef  int /*<<< orphan*/  TIFFDirEntry ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */
 int TIFFReadDirEntryArrayWithLimit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum TIFFReadDirEntryErr TIFFReadDirEntryArray(TIFF* tif, TIFFDirEntry* direntry, uint32* count, uint32 desttypesize, void** value)
{
    return TIFFReadDirEntryArrayWithLimit(tif, direntry, count,
                                          desttypesize, value, ~((uint64)0));
}