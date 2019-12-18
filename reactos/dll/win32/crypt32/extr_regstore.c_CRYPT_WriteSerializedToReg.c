#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BlobW ; 
 int /*<<< orphan*/  CRYPT_HashToStr (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  REG_BINARY ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegCreateKeyExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RegSetValueExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL CRYPT_WriteSerializedToReg(HKEY key, DWORD flags, const BYTE *hash, const BYTE *buf,
 DWORD len)
{
    WCHAR asciiHash[20 * 2 + 1];
    LONG rc;
    HKEY subKey;
    BOOL ret;

    CRYPT_HashToStr(hash, asciiHash);
    rc = RegCreateKeyExW(key, asciiHash, 0, NULL, flags, KEY_ALL_ACCESS, NULL,
     &subKey, NULL);
    if (!rc)
    {
        rc = RegSetValueExW(subKey, BlobW, 0, REG_BINARY, buf, len);
        RegCloseKey(subKey);
    }
    if (!rc)
        ret = TRUE;
    else
    {
        SetLastError(rc);
        ret = FALSE;
    }
    return ret;
}