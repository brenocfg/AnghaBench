#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cbData; scalar_t__* pbData; } ;
typedef  TYPE_1__ CERT_NAME_BLOB ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL CRYPT_IsEmptyName(const CERT_NAME_BLOB *name)
{
    BOOL empty;

    if (!name->cbData)
        empty = TRUE;
    else if (name->cbData == 2 && name->pbData[1] == 0)
    {
        /* An empty sequence is also empty */
        empty = TRUE;
    }
    else
        empty = FALSE;
    return empty;
}