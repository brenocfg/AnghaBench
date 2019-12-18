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
typedef  int /*<<< orphan*/  SAFEARRAY ;
typedef  int /*<<< orphan*/ * LPDWORD ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */

__attribute__((used)) static inline void SAFEARRAY_SetHiddenDWORD(SAFEARRAY* psa, DWORD dw)
{
  /* Implementation data is stored in the 4 bytes before the header */
  LPDWORD lpDw = (LPDWORD)psa;
  lpDw[-1] = dw;
}