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
struct TYPE_3__ {int /*<<< orphan*/  arc4ctx; } ;
typedef  int /*<<< orphan*/  HPDF_UINT ;
typedef  TYPE_1__* HPDF_Encrypt ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ARC4CryptBuf (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
HPDF_Encrypt_CryptBuf  (HPDF_Encrypt  attr,
                        const HPDF_BYTE   *src,
                        HPDF_BYTE         *dst,
                        HPDF_UINT         len)
{
    ARC4CryptBuf(&attr->arc4ctx, src, dst, len);
}