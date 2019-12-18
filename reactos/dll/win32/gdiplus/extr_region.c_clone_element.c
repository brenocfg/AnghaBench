#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* right; TYPE_3__* left; } ;
struct TYPE_9__ {TYPE_1__ combine; int /*<<< orphan*/  path; int /*<<< orphan*/  rect; } ;
struct TYPE_10__ {int type; TYPE_2__ elementdata; } ;
typedef  TYPE_3__ region_element ;
typedef  int /*<<< orphan*/  GpStatus ;

/* Variables and functions */
 int /*<<< orphan*/  GdipClonePath (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ok ; 
 int /*<<< orphan*/  OutOfMemory ; 
#define  RegionDataEmptyRect 131 
#define  RegionDataInfiniteRect 130 
#define  RegionDataPath 129 
#define  RegionDataRect 128 
 int /*<<< orphan*/  delete_element (TYPE_3__*) ; 
 TYPE_3__* heap_alloc_zero (int) ; 

__attribute__((used)) static inline GpStatus clone_element(const region_element* element,
        region_element** element2)
{
    GpStatus stat;

    /* root node is allocated with GpRegion */
    if(!*element2){
        *element2 = heap_alloc_zero(sizeof(region_element));
        if (!*element2)
            return OutOfMemory;
    }

    (*element2)->type = element->type;

    switch (element->type)
    {
        case RegionDataRect:
            (*element2)->elementdata.rect = element->elementdata.rect;
            return Ok;
        case RegionDataEmptyRect:
        case RegionDataInfiniteRect:
            return Ok;
        case RegionDataPath:
            stat = GdipClonePath(element->elementdata.path, &(*element2)->elementdata.path);
            if (stat == Ok) return Ok;
            break;
        default:
            (*element2)->elementdata.combine.left  = NULL;
            (*element2)->elementdata.combine.right = NULL;

            stat = clone_element(element->elementdata.combine.left,
                    &(*element2)->elementdata.combine.left);
            if (stat == Ok)
            {
                stat = clone_element(element->elementdata.combine.right,
                        &(*element2)->elementdata.combine.right);
                if (stat == Ok) return Ok;
            }
            break;
    }

    delete_element(*element2);
    *element2 = NULL;
    return stat;
}