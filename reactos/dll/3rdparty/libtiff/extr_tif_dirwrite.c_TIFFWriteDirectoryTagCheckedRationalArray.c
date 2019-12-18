#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  uint16 ;
struct TYPE_4__ {int tif_flags; int /*<<< orphan*/  tif_clientdata; } ;
typedef  int /*<<< orphan*/  TIFFDirEntry ;
typedef  TYPE_1__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  TIFFSwabArrayOfLong (int*,int) ; 
 int TIFFWriteDirectoryTagData (TYPE_1__*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  TIFF_RATIONAL ; 
 int TIFF_SWAB ; 
 int /*<<< orphan*/  _TIFFfree (int*) ; 
 int* _TIFFmalloc (int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
TIFFWriteDirectoryTagCheckedRationalArray(TIFF* tif, uint32* ndir, TIFFDirEntry* dir, uint16 tag, uint32 count, float* value)
{
	static const char module[] = "TIFFWriteDirectoryTagCheckedRationalArray";
	uint32* m;
	float* na;
	uint32* nb;
	uint32 nc;
	int o;
	assert(sizeof(uint32)==4);
	m=_TIFFmalloc(count*2*sizeof(uint32));
	if (m==NULL)
	{
		TIFFErrorExt(tif->tif_clientdata,module,"Out of memory");
		return(0);
	}
	for (na=value, nb=m, nc=0; nc<count; na++, nb+=2, nc++)
	{
		if (*na<=0.0 || *na != *na)
		{
			nb[0]=0;
			nb[1]=1;
		}
		else if (*na >= 0 && *na <= (float)0xFFFFFFFFU &&
                         *na==(float)(uint32)(*na))
		{
			nb[0]=(uint32)(*na);
			nb[1]=1;
		}
		else if (*na<1.0)
		{
			nb[0]=(uint32)((double)(*na)*0xFFFFFFFF);
			nb[1]=0xFFFFFFFF;
		}
		else
		{
			nb[0]=0xFFFFFFFF;
			nb[1]=(uint32)((double)0xFFFFFFFF/(*na));
		}
	}
	if (tif->tif_flags&TIFF_SWAB)
		TIFFSwabArrayOfLong(m,count*2);
	o=TIFFWriteDirectoryTagData(tif,ndir,dir,tag,TIFF_RATIONAL,count,count*8,&m[0]);
	_TIFFfree(m);
	return(o);
}