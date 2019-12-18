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
typedef  int USHORT ;
typedef  int* PUCHAR ;
typedef  scalar_t__ PISAPNP_IDENTIFIER ;

/* Variables and functions */
 int ISAPNP_LFSR_SEED ; 
 int NextLFSR (int,int) ; 

__attribute__((used)) static
USHORT
IsaPnpChecksum(PISAPNP_IDENTIFIER Identifier)
{
  USHORT i,j, Lfsr, Byte;

  Lfsr = ISAPNP_LFSR_SEED;
  for (i = 0; i < 8; i++)
  {
    Byte = *(((PUCHAR)Identifier) + i);
    for (j = 0; j < 8; j++)
    {
      Lfsr = NextLFSR(Lfsr, Byte);
      Byte >>= 1;
    }
  }

  return Lfsr;
}