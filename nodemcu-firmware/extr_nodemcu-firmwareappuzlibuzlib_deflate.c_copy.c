#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int min; int max; int code; scalar_t__ extraBits; } ;
typedef  TYPE_1__ codeRecord ;
struct TYPE_6__ {TYPE_1__* distCodes; TYPE_1__* lenCodes; } ;
struct TYPE_5__ {int /*<<< orphan*/  compDisabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_COUNT (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int distCodes_LEN ; 
 TYPE_3__* dynamicTables ; 
 int lenCodes_LEN ; 
 TYPE_2__* oBuf ; 
 int /*<<< orphan*/  outBits (int,scalar_t__) ; 
 int /*<<< orphan*/  outBitsRev (int,int) ; 

void copy (int distance, int len) {
  DBG_COUNT(7);
  const codeRecord *lenCodes  = dynamicTables->lenCodes, *l;
  const codeRecord *distCodes = dynamicTables->distCodes, *d;
  int i, j, k;

  assert(!oBuf->compDisabled);

  while (len > 0) {
   /*
    * We can transmit matches of lengths 3 through 258
    * inclusive. So if len exceeds 258, we must transmit in
    * several steps, with 258 or less in each step.
    *
    * Specifically: if len >= 261, we can transmit 258 and be
    * sure of having at least 3 left for the next step. And if
    * len <= 258, we can just transmit len. But if len == 259
    * or 260, we must transmit len-3.
    */
    int thislen = (len > 260 ? 258 : len <= 258 ? len : len - 3);
    len -= thislen;
    /*
     * Binary-search to find which length code we're
     * transmitting.
     */
    i = -1;
    j = lenCodes_LEN;
    while (1) {
      assert(j - i >= 2);
      k = (j + i) / 2;
      if (thislen < lenCodes[k].min)
        j = k;
      else if (thislen > lenCodes[k].max)
        i = k;
      else {
        l = &lenCodes[k];
        break;                 /* found it! */
      }
    }
    /*
     * Transmit the length code. 256-279 are seven bits
     * starting at 0000000; 280-287 are eight bits starting at
     * 11000000.
     */
    if (l->code <= 279) {
      outBitsRev((l->code - 256) * 2, 7);
    } else {
      outBitsRev(0xc0 - 280 + l->code, 8);
    }
    /*
     * Transmit the extra bits.
     */
    if (l->extraBits)
      outBits(thislen - l->min, l->extraBits);
    /*
     * Binary-search to find which distance code we're
     * transmitting.
     */
    i = -1;
    j = distCodes_LEN;
    while (1) {
      assert(j - i >= 2);
      k = (j + i) / 2;
      if (distance < distCodes[k].min)
        j = k;
      else if (distance > distCodes[k].max)
        i = k;
      else {
        d = &distCodes[k];
        break;                 /* found it! */
      }
    }

    /*
     * Transmit the distance code. Five bits starting at 00000.
     */
    outBitsRev(d->code * 8, 5);

    /*
     * Transmit the extra bits.
     */
    if (d->extraBits)
      outBits(distance - d->min, d->extraBits);
  }
}