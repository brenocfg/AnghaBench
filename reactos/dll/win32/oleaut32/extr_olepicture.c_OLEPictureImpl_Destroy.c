#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  hemf; } ;
struct TYPE_13__ {int /*<<< orphan*/  hicon; } ;
struct TYPE_12__ {int /*<<< orphan*/  hmeta; } ;
struct TYPE_11__ {int /*<<< orphan*/ * hbitmap; } ;
struct TYPE_15__ {TYPE_4__ emf; TYPE_3__ icon; TYPE_2__ wmf; TYPE_1__ bmp; } ;
struct TYPE_16__ {int picType; TYPE_5__ u; } ;
struct TYPE_17__ {struct TYPE_17__* data; TYPE_6__ desc; int /*<<< orphan*/ * hbmXor; int /*<<< orphan*/ * hbmMask; scalar_t__ fOwn; scalar_t__ pCP; } ;
typedef  TYPE_7__ OLEPictureImpl ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteEnhMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  IConnectionPoint_Release (scalar_t__) ; 
#define  PICTYPE_BITMAP 133 
#define  PICTYPE_ENHMETAFILE 132 
#define  PICTYPE_ICON 131 
#define  PICTYPE_METAFILE 130 
#define  PICTYPE_NONE 129 
#define  PICTYPE_UNINITIALIZED 128 
 int /*<<< orphan*/  TRACE (char*,TYPE_7__*) ; 

__attribute__((used)) static void OLEPictureImpl_Destroy(OLEPictureImpl* Obj)
{
  TRACE("(%p)\n", Obj);

  if (Obj->pCP)
    IConnectionPoint_Release(Obj->pCP);

  if(Obj->fOwn) { /* We need to destroy the picture */
    switch(Obj->desc.picType) {
    case PICTYPE_BITMAP:
      DeleteObject(Obj->desc.u.bmp.hbitmap);
      if (Obj->hbmMask != NULL) DeleteObject(Obj->hbmMask);
      if (Obj->hbmXor != NULL) DeleteObject(Obj->hbmXor);
      break;
    case PICTYPE_METAFILE:
      DeleteMetaFile(Obj->desc.u.wmf.hmeta);
      break;
    case PICTYPE_ICON:
      DestroyIcon(Obj->desc.u.icon.hicon);
      break;
    case PICTYPE_ENHMETAFILE:
      DeleteEnhMetaFile(Obj->desc.u.emf.hemf);
      break;
    case PICTYPE_NONE:
    case PICTYPE_UNINITIALIZED:
      /* Nothing to do */
      break;
    default:
      FIXME("Unsupported type %d - unable to delete\n", Obj->desc.picType);
      break;
    }
  }
  HeapFree(GetProcessHeap(), 0, Obj->data);
  HeapFree(GetProcessHeap(), 0, Obj);
}