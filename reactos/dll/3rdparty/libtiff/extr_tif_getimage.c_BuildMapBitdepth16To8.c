#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8 ;
typedef  int uint32 ;
struct TYPE_5__ {scalar_t__* Bitdepth16To8; TYPE_1__* tif; } ;
struct TYPE_4__ {int /*<<< orphan*/  tif_clientdata; } ;
typedef  TYPE_2__ TIFFRGBAImage ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*) ; 
 scalar_t__* _TIFFmalloc (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
BuildMapBitdepth16To8(TIFFRGBAImage* img)
{
	static const char module[]="BuildMapBitdepth16To8";
	uint8* m;
	uint32 n;
	assert(img->Bitdepth16To8==NULL);
	img->Bitdepth16To8=_TIFFmalloc(65536);
	if (img->Bitdepth16To8==NULL)
	{
		TIFFErrorExt(img->tif->tif_clientdata,module,"Out of memory");
		return(0);
	}
	m=img->Bitdepth16To8;
	for (n=0; n<65536; n++)
		*m++=(uint8)((n+128)/257);
	return(1);
}