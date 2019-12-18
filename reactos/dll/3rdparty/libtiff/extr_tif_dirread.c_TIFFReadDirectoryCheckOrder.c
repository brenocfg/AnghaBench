#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16 ;
struct TYPE_6__ {int /*<<< orphan*/  tif_clientdata; } ;
struct TYPE_5__ {scalar_t__ tdir_tag; } ;
typedef  TYPE_1__ TIFFDirEntry ;
typedef  TYPE_2__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFWarningExt (int /*<<< orphan*/ ,char const*,char*) ; 

__attribute__((used)) static void
TIFFReadDirectoryCheckOrder(TIFF* tif, TIFFDirEntry* dir, uint16 dircount)
{
	static const char module[] = "TIFFReadDirectoryCheckOrder";
	uint16 m;
	uint16 n;
	TIFFDirEntry* o;
	m=0;
	for (n=0, o=dir; n<dircount; n++, o++)
	{
		if (o->tdir_tag<m)
		{
			TIFFWarningExt(tif->tif_clientdata,module,
			    "Invalid TIFF directory; tags are not sorted in ascending order");
			break;
		}
		m=o->tdir_tag+1;
	}
}