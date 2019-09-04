#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_9__ {int (* vgetfield ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {TYPE_1__ tif_tagmethods; } ;
struct TYPE_10__ {int /*<<< orphan*/  field_bit; } ;
typedef  TYPE_2__ TIFFField ;
typedef  TYPE_3__ TIFF ;

/* Variables and functions */
 scalar_t__ TIFFFieldSet (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* TIFFFindField (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIFF_ANY ; 
 scalar_t__ isPseudoTag (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
TIFFVGetField(TIFF* tif, uint32 tag, va_list ap)
{
	const TIFFField* fip = TIFFFindField(tif, tag, TIFF_ANY);
	return (fip && (isPseudoTag(tag) || TIFFFieldSet(tif, fip->field_bit)) ?
	    (*tif->tif_tagmethods.vgetfield)(tif, tag, ap) : 0);
}