#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int blockSize; int destBlockSize; int numThreads; TYPE_1__* mtCallback; int /*<<< orphan*/  alloc; int /*<<< orphan*/ * outStream; int /*<<< orphan*/ * inStream; int /*<<< orphan*/ * progress; } ;
struct TYPE_10__ {int numBlockThreads; int blockSize; } ;
struct TYPE_13__ {TYPE_6__ mtCoder; TYPE_2__ props; int /*<<< orphan*/  alloc; TYPE_4__* coders; } ;
struct TYPE_12__ {int /*<<< orphan*/ * enc; } ;
struct TYPE_9__ {int /*<<< orphan*/  Code; } ;
struct TYPE_11__ {TYPE_1__ funcTable; TYPE_5__* lzma2Enc; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISeqOutStream ;
typedef  int /*<<< orphan*/  ISeqInStream ;
typedef  int /*<<< orphan*/  ICompressProgress ;
typedef  TYPE_3__ CMtCallbackImp ;
typedef  TYPE_4__ CLzma2EncInt ;
typedef  scalar_t__ CLzma2EncHandle ;
typedef  TYPE_5__ CLzma2Enc ;

/* Variables and functions */
 int /*<<< orphan*/  Lzma2Enc_EncodeMt1 (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LzmaEnc_Create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MtCallbackImp_Code ; 
 int /*<<< orphan*/  MtCoder_Code (TYPE_6__*) ; 
 int /*<<< orphan*/  SZ_ERROR_MEM ; 

SRes Lzma2Enc_Encode(CLzma2EncHandle pp,
    ISeqOutStream *outStream, ISeqInStream *inStream, ICompressProgress *progress)
{
  CLzma2Enc *p = (CLzma2Enc *)pp;
  int i;

  for (i = 0; i < p->props.numBlockThreads; i++)
  {
    CLzma2EncInt *t = &p->coders[i];
    if (t->enc == NULL)
    {
      t->enc = LzmaEnc_Create(p->alloc);
      if (t->enc == NULL)
        return SZ_ERROR_MEM;
    }
  }

  #ifndef _7ZIP_ST
  if (p->props.numBlockThreads <= 1)
  #endif
    return Lzma2Enc_EncodeMt1(&p->coders[0], p, outStream, inStream, progress);

  #ifndef _7ZIP_ST

  {
    CMtCallbackImp mtCallback;

    mtCallback.funcTable.Code = MtCallbackImp_Code;
    mtCallback.lzma2Enc = p;
    
    p->mtCoder.progress = progress;
    p->mtCoder.inStream = inStream;
    p->mtCoder.outStream = outStream;
    p->mtCoder.alloc = p->alloc;
    p->mtCoder.mtCallback = &mtCallback.funcTable;

    p->mtCoder.blockSize = p->props.blockSize;
    p->mtCoder.destBlockSize = p->props.blockSize + (p->props.blockSize >> 10) + 16;
    p->mtCoder.numThreads = p->props.numBlockThreads;
    
    return MtCoder_Code(&p->mtCoder);
  }
  #endif
}