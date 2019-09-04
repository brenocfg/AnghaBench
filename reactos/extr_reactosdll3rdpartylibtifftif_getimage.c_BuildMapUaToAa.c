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
typedef  int uint16 ;
struct TYPE_5__ {scalar_t__* UaToAa; TYPE_1__* tif; } ;
struct TYPE_4__ {int /*<<< orphan*/  tif_clientdata; } ;
typedef  TYPE_2__ TIFFRGBAImage ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*) ; 
 scalar_t__* _TIFFmalloc (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
BuildMapUaToAa(TIFFRGBAImage* img)
{
	static const char module[]="BuildMapUaToAa";
	uint8* m;
	uint16 na,nv;
	assert(img->UaToAa==NULL);
	img->UaToAa=_TIFFmalloc(65536);
	if (img->UaToAa==NULL)
	{
		TIFFErrorExt(img->tif->tif_clientdata,module,"Out of memory");
		return(0);
	}
	m=img->UaToAa;
	for (na=0; na<256; na++)
	{
		for (nv=0; nv<256; nv++)
			*m++=(uint8)((nv*na+127)/255);
	}
	return(1);
}