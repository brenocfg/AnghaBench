#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  obj_class; } ;
struct TYPE_8__ {scalar_t__ attr; int /*<<< orphan*/  mmgr; int /*<<< orphan*/  free_fn; TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  HPDF_Xref ;
typedef  int /*<<< orphan*/  HPDF_MMgr ;
typedef  int /*<<< orphan*/  HPDF_Encrypt_Rec ;
typedef  TYPE_2__* HPDF_EncryptDict ;
typedef  scalar_t__ HPDF_Encrypt ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_Dict_Free (TYPE_2__*) ; 
 TYPE_2__* HPDF_Dict_New (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HPDF_EncryptDict_OnFree ; 
 int /*<<< orphan*/  HPDF_Encrypt_Init (scalar_t__) ; 
 scalar_t__ HPDF_GetMem (int /*<<< orphan*/ ,int) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_OSUBCLASS_ENCRYPT ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 scalar_t__ HPDF_Xref_Add (int /*<<< orphan*/ ,TYPE_2__*) ; 

HPDF_EncryptDict
HPDF_EncryptDict_New  (HPDF_MMgr  mmgr,
                       HPDF_Xref  xref)
{
    HPDF_Encrypt attr;
    HPDF_EncryptDict dict;

    HPDF_PTRACE((" HPDF_EncryptDict_New\n"));

    dict = HPDF_Dict_New (mmgr);
    if (!dict)
        return NULL;

    dict->header.obj_class |= HPDF_OSUBCLASS_ENCRYPT;
    dict->free_fn = HPDF_EncryptDict_OnFree;

    attr = HPDF_GetMem (dict->mmgr, sizeof(HPDF_Encrypt_Rec));
    if (!attr) {
        HPDF_Dict_Free (dict);
        return NULL;
    }

    dict->attr = attr;
    HPDF_Encrypt_Init (attr);

    if (HPDF_Xref_Add (xref, dict) != HPDF_OK)
        return NULL;

    return dict;
}