#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_13__ {int td_customValueCount; TYPE_2__* td_customValues; } ;
struct TYPE_14__ {int /*<<< orphan*/  tif_flags; TYPE_4__ tif_dir; } ;
struct TYPE_12__ {scalar_t__ field_bit; } ;
struct TYPE_11__ {int /*<<< orphan*/  value; TYPE_1__* info; } ;
struct TYPE_10__ {scalar_t__ field_tag; } ;
typedef  TYPE_2__ TIFFTagValue ;
typedef  TYPE_3__ TIFFField ;
typedef  TYPE_4__ TIFFDirectory ;
typedef  TYPE_5__ TIFF ;

/* Variables and functions */
 scalar_t__ FIELD_CUSTOM ; 
 int /*<<< orphan*/  TIFFClrFieldBit (TYPE_5__*,scalar_t__) ; 
 TYPE_3__* TIFFFieldWithTag (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  TIFF_DIRTYDIRECT ; 
 int /*<<< orphan*/  _TIFFfree (int /*<<< orphan*/ ) ; 

int
TIFFUnsetField(TIFF* tif, uint32 tag)
{
    const TIFFField *fip =  TIFFFieldWithTag(tif, tag);
    TIFFDirectory* td = &tif->tif_dir;

    if( !fip )
        return 0;

    if( fip->field_bit != FIELD_CUSTOM )
        TIFFClrFieldBit(tif, fip->field_bit);
    else
    {
        TIFFTagValue *tv = NULL;
        int i;

        for (i = 0; i < td->td_customValueCount; i++) {
                
            tv = td->td_customValues + i;
            if( tv->info->field_tag == tag )
                break;
        }

        if( i < td->td_customValueCount )
        {
            _TIFFfree(tv->value);
            for( ; i < td->td_customValueCount-1; i++) {
                td->td_customValues[i] = td->td_customValues[i+1];
            }
            td->td_customValueCount--;
        }
    }
        
    tif->tif_flags |= TIFF_DIRTYDIRECT;

    return (1);
}