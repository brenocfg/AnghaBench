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
struct TYPE_3__ {int cbData; int /*<<< orphan*/ * pbData; } ;
typedef  int DWORD ;
typedef  TYPE_1__ CRYPT_HASH_BLOB ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */

__attribute__((used)) static void CRYPT_ReverseBytes(CRYPT_HASH_BLOB *hash)
{
    DWORD i;
    BYTE tmp;

    for (i = 0; i < hash->cbData / 2; i++)
    {
        tmp = hash->pbData[hash->cbData - i - 1];
        hash->pbData[hash->cbData - i - 1] = hash->pbData[i];
        hash->pbData[i] = tmp;
    }
}