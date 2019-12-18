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
typedef  scalar_t__ VARTYPE ;
struct TYPE_5__ {void* fFeatures; } ;
typedef  TYPE_1__ SAFEARRAY ;

/* Variables and functions */
 void* FADF_HAVEIID ; 
 void* FADF_HAVEVARTYPE ; 
 void* FADF_RECORD ; 
 int /*<<< orphan*/  IID_IDispatch ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  SAFEARRAY_SetHiddenDWORD (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  SafeArraySetIID (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ VT_DISPATCH ; 
 scalar_t__ VT_RECORD ; 
 scalar_t__ VT_UNKNOWN ; 

__attribute__((used)) static void SAFEARRAY_SetFeatures(VARTYPE vt, SAFEARRAY *psa)
{
  /* Set the IID if we have one, otherwise set the type */
  if (vt == VT_DISPATCH)
  {
    psa->fFeatures = FADF_HAVEIID;
    SafeArraySetIID(psa, &IID_IDispatch);
  }
  else if (vt == VT_UNKNOWN)
  {
    psa->fFeatures = FADF_HAVEIID;
    SafeArraySetIID(psa, &IID_IUnknown);
  }
  else if (vt == VT_RECORD)
    psa->fFeatures = FADF_RECORD;
  else
  {
    psa->fFeatures = FADF_HAVEVARTYPE;
    SAFEARRAY_SetHiddenDWORD(psa, vt);
  }
}