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
struct TYPE_4__ {int /*<<< orphan*/  e; int /*<<< orphan*/  N; } ;
struct TYPE_5__ {TYPE_1__ rsa; } ;
typedef  TYPE_2__ KEY_CONTEXT ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ mp_get_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_to_unsigned_bin (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mp_unsigned_bin_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reverse_bytes (int /*<<< orphan*/ *,scalar_t__) ; 

BOOL export_public_key_impl(BYTE *pbDest, const KEY_CONTEXT *pKeyContext, DWORD dwKeyLen,DWORD *pdwPubExp)
{
    mp_to_unsigned_bin(&pKeyContext->rsa.N, pbDest);
    reverse_bytes(pbDest, mp_unsigned_bin_size(&pKeyContext->rsa.N));
    if (mp_unsigned_bin_size(&pKeyContext->rsa.N) < dwKeyLen)
        memset(pbDest + mp_unsigned_bin_size(&pKeyContext->rsa.N), 0,
               dwKeyLen - mp_unsigned_bin_size(&pKeyContext->rsa.N));
    *pdwPubExp = (DWORD)mp_get_int(&pKeyContext->rsa.e);
    return TRUE;
}