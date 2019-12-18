#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sltg_ref_lookup_t ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_13__ {int vt; } ;
struct TYPE_12__ {TYPE_4__* tdescAlias; int /*<<< orphan*/  pTypeLib; } ;
struct TYPE_11__ {int href_table; } ;
struct TYPE_10__ {int tdescalias_vt; scalar_t__ simple_alias; } ;
typedef  int /*<<< orphan*/  TYPEDESC ;
typedef  TYPE_1__ SLTG_TypeInfoTail ;
typedef  TYPE_2__ SLTG_TypeInfoHeader ;
typedef  int /*<<< orphan*/  SLTG_RefInfo ;
typedef  TYPE_3__ ITypeInfoImpl ;

/* Variables and functions */
 int /*<<< orphan*/ * SLTG_DoRefs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SLTG_DoType (int /*<<< orphan*/ *,char*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* heap_alloc (int) ; 
 TYPE_4__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SLTG_ProcessAlias(char *pBlk, ITypeInfoImpl *pTI,
			      char *pNameTable, SLTG_TypeInfoHeader *pTIHeader,
			      const SLTG_TypeInfoTail *pTITail)
{
  WORD *pType;
  sltg_ref_lookup_t *ref_lookup = NULL;

  if (pTITail->simple_alias) {
      /* if simple alias, no more processing required */
      pTI->tdescAlias = heap_alloc_zero(sizeof(TYPEDESC));
      pTI->tdescAlias->vt = pTITail->tdescalias_vt;
      return;
  }

  if(pTIHeader->href_table != 0xffffffff) {
      ref_lookup = SLTG_DoRefs((SLTG_RefInfo*)((char *)pTIHeader + pTIHeader->href_table), pTI->pTypeLib,
		  pNameTable);
  }

  /* otherwise it is an offset to a type */
  pType = (WORD *)(pBlk + pTITail->tdescalias_vt);

  pTI->tdescAlias = heap_alloc(sizeof(TYPEDESC));
  SLTG_DoType(pType, pBlk, pTI->tdescAlias, ref_lookup);

  heap_free(ref_lookup);
}