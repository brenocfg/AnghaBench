#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_3__ {int /*<<< orphan*/  tdir_offset; } ;
typedef  TYPE_1__ TIFFDirEntry ;
typedef  int /*<<< orphan*/  TIFF ;

/* Variables and functions */

__attribute__((used)) static void TIFFReadDirEntryCheckedByte(TIFF* tif, TIFFDirEntry* direntry, uint8* value)
{
	(void) tif;
	*value=*(uint8*)(&direntry->tdir_offset);
}