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
typedef  int UInt32 ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  CSzData ;
typedef  scalar_t__ Byte ;

/* Variables and functions */
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  SzReadByte (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static SRes SzReadUInt32(CSzData *sd, UInt32 *value)
{
  int i;
  *value = 0;
  for (i = 0; i < 4; i++)
  {
    Byte b;
    RINOK(SzReadByte(sd, &b));
    *value |= ((UInt32)(b) << (8 * i));
  }
  return SZ_OK;
}