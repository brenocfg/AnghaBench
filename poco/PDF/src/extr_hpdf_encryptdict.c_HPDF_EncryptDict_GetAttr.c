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
struct TYPE_5__ {scalar_t__ attr; } ;
struct TYPE_4__ {int obj_class; } ;
typedef  TYPE_1__ HPDF_Obj_Header ;
typedef  TYPE_2__* HPDF_EncryptDict ;
typedef  int /*<<< orphan*/ * HPDF_Encrypt ;

/* Variables and functions */
 int HPDF_OCLASS_DICT ; 
 int HPDF_OSUBCLASS_ENCRYPT ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 

HPDF_Encrypt
HPDF_EncryptDict_GetAttr (HPDF_EncryptDict  dict)
{
    HPDF_Obj_Header *header = (HPDF_Obj_Header *)dict;

    HPDF_PTRACE((" HPDF_EncryptDict_GetAttr\n"));

    if (dict && dict->attr &&
        (header->obj_class == (HPDF_OCLASS_DICT | HPDF_OSUBCLASS_ENCRYPT)))
        return (HPDF_Encrypt)dict->attr;

    return NULL;
}