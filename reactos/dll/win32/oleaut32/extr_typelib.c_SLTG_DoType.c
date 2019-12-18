#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sltg_ref_lookup_t ;
typedef  int WORD ;
struct TYPE_9__ {int cDims; int /*<<< orphan*/  rgsabound; } ;
struct TYPE_7__ {TYPE_3__* lptdesc; TYPE_1__* lpadesc; int /*<<< orphan*/  hreftype; } ;
struct TYPE_8__ {int vt; TYPE_2__ u; } ;
struct TYPE_6__ {int cDims; TYPE_3__ tdescElem; int /*<<< orphan*/  rgbounds; } ;
typedef  TYPE_3__ TYPEDESC ;
typedef  int /*<<< orphan*/  SAFEARRAYBOUND ;
typedef  TYPE_4__ SAFEARRAY ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  ARRAYDESC ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  VT_CARRAY 131 
#define  VT_PTR 130 
#define  VT_SAFEARRAY 129 
#define  VT_USERDEFINED 128 
 void* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sltg_get_typelib_ref (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static WORD *SLTG_DoType(WORD *pType, char *pBlk, TYPEDESC *pTD, const sltg_ref_lookup_t *ref_lookup)
{
    BOOL done = FALSE;

    while(!done) {
        if((*pType & 0xe00) == 0xe00) {
	    pTD->vt = VT_PTR;
	    pTD->u.lptdesc = heap_alloc_zero(sizeof(TYPEDESC));
	    pTD = pTD->u.lptdesc;
	}
	switch(*pType & 0x3f) {
	case VT_PTR:
	    pTD->vt = VT_PTR;
	    pTD->u.lptdesc = heap_alloc_zero(sizeof(TYPEDESC));
	    pTD = pTD->u.lptdesc;
	    break;

	case VT_USERDEFINED:
	    pTD->vt = VT_USERDEFINED;
            sltg_get_typelib_ref(ref_lookup, *(++pType) / 4, &pTD->u.hreftype);
	    done = TRUE;
	    break;

	case VT_CARRAY:
	  {
	    /* *(pType+1) is offset to a SAFEARRAY, *(pType+2) is type of
	       array */

	    SAFEARRAY *pSA = (SAFEARRAY *)(pBlk + *(++pType));

	    pTD->vt = VT_CARRAY;
	    pTD->u.lpadesc = heap_alloc_zero(sizeof(ARRAYDESC) + (pSA->cDims - 1) * sizeof(SAFEARRAYBOUND));
	    pTD->u.lpadesc->cDims = pSA->cDims;
	    memcpy(pTD->u.lpadesc->rgbounds, pSA->rgsabound,
		   pSA->cDims * sizeof(SAFEARRAYBOUND));

	    pTD = &pTD->u.lpadesc->tdescElem;
	    break;
	  }

	case VT_SAFEARRAY:
	  {
	    /* FIXME: *(pType+1) gives an offset to SAFEARRAY, is this
	       useful? */

	    pType++;
	    pTD->vt = VT_SAFEARRAY;
	    pTD->u.lptdesc = heap_alloc_zero(sizeof(TYPEDESC));
	    pTD = pTD->u.lptdesc;
	    break;
	  }
	default:
	    pTD->vt = *pType & 0x3f;
	    done = TRUE;
	    break;
	}
	pType++;
    }
    return pType;
}