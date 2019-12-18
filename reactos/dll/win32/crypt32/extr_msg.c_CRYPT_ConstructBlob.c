#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pbData; scalar_t__ cbData; } ;
typedef  TYPE_1__ CRYPT_DATA_BLOB ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/ * CryptMemAlloc (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static BOOL CRYPT_ConstructBlob(CRYPT_DATA_BLOB *out, const CRYPT_DATA_BLOB *in)
{
    BOOL ret = TRUE;

    out->cbData = in->cbData;
    if (out->cbData)
    {
        out->pbData = CryptMemAlloc(out->cbData);
        if (out->pbData)
            memcpy(out->pbData, in->pbData, out->cbData);
        else
            ret = FALSE;
    }
    else
        out->pbData = NULL;
    return ret;
}