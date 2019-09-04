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
typedef  scalar_t__ DWORD ;
typedef  int BYTE ;

/* Variables and functions */

DWORD kuhl_m_crypto_extractor_GetKeySizeForEncryptMemory(DWORD size)
{
  DWORD v1;
  v1 = size - 20;
  if (((BYTE) size - 20) & 0xf)
    v1 += 16 - (((BYTE) size - 20) & 0xf);
  return v1 + 20;
}