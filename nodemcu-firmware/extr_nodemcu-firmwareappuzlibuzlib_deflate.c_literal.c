#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uchar ;
struct TYPE_2__ {scalar_t__ compDisabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_COUNT (int) ; 
 int /*<<< orphan*/  DBG_PRINT (char*,int,int) ; 
 TYPE_1__* oBuf ; 
 int /*<<< orphan*/  outBits (int,int) ; 
 int /*<<< orphan*/  outBitsRev (int,int) ; 

void literal (uchar c) {
  DBG_COUNT(6);
  DBG_PRINT("sym: %02x   %c\n", c, c);
  if (oBuf->compDisabled) {
    /* We're in an uncompressed block, so just output the byte. */
    outBits(c, 8);
  } else if (c <= 143) {
    /* 0 through 143 are 8 bits long starting at 00110000. */
    outBitsRev(0x30 + c, 8);
  } else {
    /* 144 through 255 are 9 bits long starting at 110010000. */
    outBits(1, 1);
    outBitsRev(0x90 - 144 + c, 8);
  }
}