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
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_2__ {int len; int size; int /*<<< orphan*/ * buffer; scalar_t__ bits; scalar_t__ nBits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_COUNT (int) ; 
 int /*<<< orphan*/  DBG_PRINT (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* oBuf ; 
 int /*<<< orphan*/  resizeBuffer () ; 

void outBytes(void *bytes, int nBytes) {
  DBG_COUNT(5);
  int i;
  if (oBuf->len >= oBuf->size - nBytes)
    resizeBuffer();

  /* Note that byte output dumps any bits data so the caller must */
  /* flush this first, if necessary */
  oBuf->nBits = oBuf->bits  = 0;
  for (i = 0; i < nBytes; i++) {
    DBG_PRINT("%02x-", *((uchar*)bytes+i));
    oBuf->buffer[oBuf->len++] = *((uchar*)bytes+i);
  }
}