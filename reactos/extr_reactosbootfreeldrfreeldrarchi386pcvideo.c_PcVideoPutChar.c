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
typedef  int /*<<< orphan*/  VOID ;
typedef  int USHORT ;
typedef  scalar_t__ ULONG_PTR ;
typedef  scalar_t__ UCHAR ;

/* Variables and functions */
 unsigned int BytesPerScanLine ; 
 scalar_t__ VIDEOTEXT_MEM_ADDRESS ; 

VOID
PcVideoPutChar(int Ch, UCHAR Attr, unsigned X, unsigned Y)
{
  USHORT *BufPtr;

  BufPtr = (USHORT *) (ULONG_PTR)(VIDEOTEXT_MEM_ADDRESS + Y * BytesPerScanLine + X * 2);
  *BufPtr = ((USHORT) Attr << 8) | (Ch & 0xff);
}