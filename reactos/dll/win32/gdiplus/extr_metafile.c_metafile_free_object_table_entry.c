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
struct TYPE_4__ {int /*<<< orphan*/ * object; int /*<<< orphan*/  image_attributes; int /*<<< orphan*/  font; int /*<<< orphan*/  image; int /*<<< orphan*/  region; int /*<<< orphan*/  path; int /*<<< orphan*/  pen; int /*<<< orphan*/  brush; } ;
struct emfplus_object {int type; TYPE_1__ u; } ;
struct TYPE_5__ {struct emfplus_object* objtable; } ;
typedef  TYPE_2__ GpMetafile ;
typedef  size_t BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  GdipDeleteBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipDeleteFont (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipDeletePath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipDeletePen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipDeleteRegion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipDisposeImage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipDisposeImageAttributes (int /*<<< orphan*/ ) ; 
#define  ObjectTypeBrush 135 
#define  ObjectTypeFont 134 
#define  ObjectTypeImage 133 
#define  ObjectTypeImageAttributes 132 
#define  ObjectTypeInvalid 131 
#define  ObjectTypePath 130 
#define  ObjectTypePen 129 
#define  ObjectTypeRegion 128 

__attribute__((used)) static void metafile_free_object_table_entry(GpMetafile *metafile, BYTE id)
{
    struct emfplus_object *object = &metafile->objtable[id];

    switch (object->type)
    {
    case ObjectTypeInvalid:
        break;
    case ObjectTypeBrush:
        GdipDeleteBrush(object->u.brush);
        break;
    case ObjectTypePen:
        GdipDeletePen(object->u.pen);
        break;
    case ObjectTypePath:
        GdipDeletePath(object->u.path);
        break;
    case ObjectTypeRegion:
        GdipDeleteRegion(object->u.region);
        break;
    case ObjectTypeImage:
        GdipDisposeImage(object->u.image);
        break;
    case ObjectTypeFont:
        GdipDeleteFont(object->u.font);
        break;
    case ObjectTypeImageAttributes:
        GdipDisposeImageAttributes(object->u.image_attributes);
        break;
    default:
        FIXME("not implemented for object type %u.\n", object->type);
        return;
    }

    object->type = ObjectTypeInvalid;
    object->u.object = NULL;
}