#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int td_compression; } ;
struct TYPE_8__ {int /*<<< orphan*/  tif_name; int /*<<< orphan*/  tif_clientdata; TYPE_1__ tif_dir; } ;
struct TYPE_7__ {char* name; } ;
typedef  TYPE_2__ TIFFCodec ;
typedef  TYPE_3__ TIFF ;

/* Variables and functions */
 int /*<<< orphan*/  TIFFErrorExt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_2__* TIFFFindCODEC (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int
_notConfigured(TIFF* tif)
{
	const TIFFCodec* c = TIFFFindCODEC(tif->tif_dir.td_compression);
        char compression_code[20];
        
        sprintf(compression_code, "%d",tif->tif_dir.td_compression );
	TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
                     "%s compression support is not configured", 
                     c ? c->name : compression_code );
	return (0);
}