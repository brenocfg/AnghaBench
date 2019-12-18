#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* outStream; } ;
struct TYPE_10__ {int writeEndMark; TYPE_1__ rc; } ;
struct TYPE_8__ {int /*<<< orphan*/  Write; } ;
struct TYPE_9__ {scalar_t__ overflow; scalar_t__ rem; TYPE_2__ funcTable; int /*<<< orphan*/ * data; } ;
typedef  scalar_t__ SizeT ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  int /*<<< orphan*/  ICompressProgress ;
typedef  TYPE_3__ CSeqOutStreamBuf ;
typedef  scalar_t__ CLzmaEncHandle ;
typedef  TYPE_4__ CLzmaEnc ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ False ; 
 scalar_t__ LzmaEnc_Encode2 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ LzmaEnc_MemPrepare (scalar_t__,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LzmaEnc_SetInputBuf (TYPE_4__*,int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  MyWrite ; 
 scalar_t__ SZ_ERROR_OUTPUT_EOF ; 
 scalar_t__ SZ_OK ; 

SRes LzmaEnc_MemEncode(CLzmaEncHandle pp, Byte *dest, SizeT *destLen, const Byte *src, SizeT srcLen,
    int writeEndMark, ICompressProgress *progress, ISzAlloc *alloc, ISzAlloc *allocBig)
{
  SRes res;
  CLzmaEnc *p = (CLzmaEnc *)pp;

  CSeqOutStreamBuf outStream;

  LzmaEnc_SetInputBuf(p, src, srcLen);

  outStream.funcTable.Write = MyWrite;
  outStream.data = dest;
  outStream.rem = *destLen;
  outStream.overflow = False;

  p->writeEndMark = writeEndMark;

  p->rc.outStream = &outStream.funcTable;
  res = LzmaEnc_MemPrepare(pp, src, srcLen, 0, alloc, allocBig);
  if (res == SZ_OK)
    res = LzmaEnc_Encode2(p, progress);

  *destLen -= outStream.rem;
  if (outStream.overflow)
    return SZ_ERROR_OUTPUT_EOF;
  return res;
}