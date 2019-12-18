#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
struct TYPE_4__ {scalar_t__ Checksum; } ;
typedef  int* PUCHAR ;
typedef  int /*<<< orphan*/  Identifier ;
typedef  TYPE_1__ ISAPNP_IDENTIFIER ;
typedef  int INT ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  EnterIsolationState () ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  HwDelay () ; 
 scalar_t__ IsaPnpChecksum (TYPE_1__*) ; 
 int ReadData (int*) ; 
 int /*<<< orphan*/  ResetCsn () ; 
 int /*<<< orphan*/  RtlZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  SendKey () ; 
 int /*<<< orphan*/  SetReadDataPort (int*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WaitForKey () ; 
 int /*<<< orphan*/  Wake (int) ; 
 int /*<<< orphan*/  WriteCsn (int) ; 

__attribute__((used)) static
INT
TryIsolate(PUCHAR ReadDataPort)
{
  ISAPNP_IDENTIFIER Identifier;
  USHORT i, j;
  BOOLEAN Seen55aa, SeenLife;
  INT Csn = 0;
  USHORT Byte, Data;

  DPRINT("Setting read data port: 0x%p\n", ReadDataPort);

  WaitForKey();
  SendKey();

  ResetCsn();
  HwDelay();
  HwDelay();

  WaitForKey();
  SendKey();
  Wake(0x00);

  SetReadDataPort(ReadDataPort);
  HwDelay();

  while (TRUE)
  {
    EnterIsolationState();
    HwDelay();

    RtlZeroMemory(&Identifier, sizeof(Identifier));

    Seen55aa = SeenLife = FALSE;
    for (i = 0; i < 9; i++)
    {
      Byte = 0;
      for (j = 0; j < 8; j++)
      {
        Data = ReadData(ReadDataPort);
        HwDelay();
        Data = ((Data << 8) | ReadData(ReadDataPort));
        HwDelay();
        Byte >>= 1;

        if (Data != 0xFFFF)
        {
           SeenLife = TRUE;
           if (Data == 0x55AA)
           {
             Byte |= 0x80;
             Seen55aa = TRUE;
           }
        }
      }
      *(((PUCHAR)&Identifier) + i) = Byte;
    }

    if (!Seen55aa)
    {
       if (Csn)
       {
         DPRINT("Found no more cards\n");
       }
       else
       {
         if (SeenLife)
         {
           DPRINT("Saw life but no cards, trying new read port\n");
           Csn = -1;
         }
         else
         {
           DPRINT("Saw no sign of life, abandoning isolation\n");
         }
       }
       break;
    }

    if (Identifier.Checksum != IsaPnpChecksum(&Identifier))
    {
        DPRINT("Bad checksum, trying next read data port\n");
        Csn = -1;
        break;
    }

    Csn++;

    WriteCsn(Csn);
    HwDelay();

    Wake(0x00);
    HwDelay();
  }

  WaitForKey();

  if (Csn > 0)
  {
    DPRINT("Found %d cards at read port 0x%p\n", Csn, ReadDataPort);
  }

  return Csn;
}