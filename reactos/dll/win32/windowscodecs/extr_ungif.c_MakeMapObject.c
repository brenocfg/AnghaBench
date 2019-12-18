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
struct TYPE_5__ {int ColorCount; int BitsPerPixel; int /*<<< orphan*/ * Colors; } ;
typedef  int /*<<< orphan*/  GifColorType ;
typedef  TYPE_1__ ColorMapObject ;

/* Variables and functions */
 int BitSize (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 TYPE_1__* ungif_alloc (int) ; 
 int /*<<< orphan*/ * ungif_calloc (int,int) ; 
 int /*<<< orphan*/  ungif_free (TYPE_1__*) ; 

__attribute__((used)) static ColorMapObject *
MakeMapObject(int ColorCount,
              const GifColorType * ColorMap) {

    ColorMapObject *Object;

    /*** FIXME: Our ColorCount has to be a power of two.  Is it necessary to
     * make the user know that or should we automatically round up instead? */
    if (ColorCount != (1 << BitSize(ColorCount))) {
        return NULL;
    }

    Object = ungif_alloc(sizeof(ColorMapObject));
    if (Object == NULL) {
        return NULL;
    }

    Object->Colors = ungif_calloc(ColorCount, sizeof(GifColorType));
    if (Object->Colors == NULL) {
        ungif_free(Object);
        return NULL;
    }

    Object->ColorCount = ColorCount;
    Object->BitsPerPixel = BitSize(ColorCount);

    if (ColorMap) {
        memcpy(Object->Colors, ColorMap, ColorCount * sizeof(GifColorType));
    }

    return (Object);
}