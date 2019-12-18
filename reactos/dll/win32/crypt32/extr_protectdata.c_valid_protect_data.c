#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cbData; scalar_t__ pbData; } ;
struct protect_data_t {int count0; int count1; int null0; int null1; TYPE_1__ info0; } ;
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  crypt_magic_str ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
BOOL valid_protect_data(const struct protect_data_t *pInfo)
{
    BOOL status=TRUE;

    TRACE("called\n");

    if (pInfo->count0 != 0x0001)
    {
        ERR("count0 != 0x0001 !\n");
        status=FALSE;
    }
    if (pInfo->count1 != 0x0001)
    {
        ERR("count0 != 0x0001 !\n");
        status=FALSE;
    }
    if (pInfo->null0 != 0x0000)
    {
        ERR("null0 != 0x0000 !\n");
        status=FALSE;
    }
    if (pInfo->null1 != 0x0000)
    {
        ERR("null1 != 0x0000 !\n");
        status=FALSE;
    }
    /* since we have no idea what info0 is used for, and it seems
     * rather constant, we can test for a Wine-specific magic string
     * there to be reasonably sure we're using data created by the Wine
     * implementation of CryptProtectData.
     */
    if (pInfo->info0.cbData!=strlen(crypt_magic_str)+1 ||
        strcmp( (LPCSTR)pInfo->info0.pbData,crypt_magic_str) != 0)
    {
        ERR("info0 magic value not matched !\n");
        status=FALSE;
    }

    if (!status)
    {
        ERR("unrecognized CryptProtectData block\n");
    }

    return status;
}