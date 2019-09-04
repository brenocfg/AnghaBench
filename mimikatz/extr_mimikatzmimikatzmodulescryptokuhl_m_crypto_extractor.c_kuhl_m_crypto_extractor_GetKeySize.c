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
typedef  int DWORD ;

/* Variables and functions */

DWORD kuhl_m_crypto_extractor_GetKeySize(DWORD bits)
{
  DWORD v4, v5, v6;
  v4 = ((bits + 7) >> 3) & 7;
  v5 = (bits + 15) >> 4;
  v6 = 8 - v4;
  if(v4)
    v6 += 8;
  return 10 * ((v6 >> 1) + v5 + 2);
}