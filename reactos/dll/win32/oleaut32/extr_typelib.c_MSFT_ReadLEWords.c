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
typedef  int /*<<< orphan*/  TLBContext ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FromLEWords (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSFT_Read (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static DWORD MSFT_ReadLEWords(void *buffer,  DWORD count, TLBContext *pcx,
                              LONG where )
{
  DWORD ret;

  ret = MSFT_Read(buffer, count, pcx, where);
  FromLEWords(buffer, ret);

  return ret;
}