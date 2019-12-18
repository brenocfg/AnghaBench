#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int cAttr; TYPE_2__* rgAttr; } ;
struct TYPE_6__ {int cValue; TYPE_1__* rgValue; scalar_t__ pszObjId; } ;
struct TYPE_5__ {scalar_t__ cbData; } ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  CRYPT_DATA_BLOB ;
typedef  TYPE_3__ CRYPT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  CRYPT_ATTRIBUTE ;

/* Variables and functions */
 size_t ALIGN_DWORD_PTR (size_t) ; 
 scalar_t__ strlen (scalar_t__) ; 

__attribute__((used)) static DWORD CRYPT_SizeOfAttributes(const CRYPT_ATTRIBUTES *attr)
{
    DWORD size = attr->cAttr * sizeof(CRYPT_ATTRIBUTE), i, j;

    for (i = 0; i < attr->cAttr; i++)
    {
        if (attr->rgAttr[i].pszObjId)
            size += strlen(attr->rgAttr[i].pszObjId) + 1;
        /* align pointer */
        size = ALIGN_DWORD_PTR(size);
        size += attr->rgAttr[i].cValue * sizeof(CRYPT_DATA_BLOB);
        for (j = 0; j < attr->rgAttr[i].cValue; j++)
            size += attr->rgAttr[i].rgValue[j].cbData;
    }
    /* align pointer again to be conservative */
    size = ALIGN_DWORD_PTR(size);
    return size;
}