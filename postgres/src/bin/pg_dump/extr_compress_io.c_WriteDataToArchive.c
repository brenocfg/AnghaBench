#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int comprAlg; } ;
typedef  TYPE_1__ CompressorState ;
typedef  int /*<<< orphan*/  ArchiveHandle ;

/* Variables and functions */
#define  COMPR_ALG_LIBZ 129 
#define  COMPR_ALG_NONE 128 
 int /*<<< orphan*/  WriteDataToArchiveNone (int /*<<< orphan*/ *,TYPE_1__*,void const*,size_t) ; 
 int /*<<< orphan*/  WriteDataToArchiveZlib (int /*<<< orphan*/ *,TYPE_1__*,void const*,size_t) ; 
 int /*<<< orphan*/  fatal (char*) ; 

void
WriteDataToArchive(ArchiveHandle *AH, CompressorState *cs,
				   const void *data, size_t dLen)
{
	switch (cs->comprAlg)
	{
		case COMPR_ALG_LIBZ:
#ifdef HAVE_LIBZ
			WriteDataToArchiveZlib(AH, cs, data, dLen);
#else
			fatal("not built with zlib support");
#endif
			break;
		case COMPR_ALG_NONE:
			WriteDataToArchiveNone(AH, cs, data, dLen);
			break;
	}
	return;
}