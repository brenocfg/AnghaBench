#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  properties ;
typedef  int UInt32 ;
struct TYPE_3__ {int /*<<< orphan*/ * Probs; int /*<<< orphan*/  Properties; } ;
typedef  int SizeT ;
typedef  int /*<<< orphan*/  CProb ;
typedef  TYPE_1__ CLzmaDecoderState ;

/* Variables and functions */
 int LZMA_PROPERTIES_SIZE ; 
 int LZMA_RESULT_DATA_ERROR ; 
 scalar_t__ LZMA_RESULT_OK ; 
 int LzmaDecode (TYPE_1__*,unsigned char*,int,int*,unsigned char*,int,int*) ; 
 scalar_t__ LzmaDecodeProperties (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int LzmaGetNumProbs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MyReadFileAndCheck (unsigned char*,unsigned char*,int) ; 
 scalar_t__ dpos ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 char* kCantAllocateMessage ; 
 char* kCantReadMessage ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int rpos ; 

int lzma_inflate(unsigned char *source, int s_len, unsigned char *dest, int *d_len)
{
  /* We use two 32-bit integers to construct 64-bit integer for file size.
     You can remove outSizeHigh, if you don't need >= 4GB supporting,
     or you can use UInt64 outSize, if your compiler supports 64-bit integers*/
  UInt32 outSize = 0;
  UInt32 outSizeHigh = 0;
  SizeT outSizeFull;
  unsigned char *outStream;
  
  int waitEOS = 1; 
  /* waitEOS = 1, if there is no uncompressed size in headers, 
   so decoder will wait EOS (End of Stream Marker) in compressed stream */

  SizeT compressedSize;
  unsigned char *inStream;

  CLzmaDecoderState state;  /* it's about 24-80 bytes structure, if int is 32-bit */
  unsigned char properties[LZMA_PROPERTIES_SIZE];

  int res;

  rpos=0; dpos=0;

  if (sizeof(UInt32) < 4)
  {
#if defined(DEBUG_ENABLE_BOOTSTRAP_PRINTF) || !defined(CFG_BOOTSTRAP_CODE)
    printf("LZMA decoder needs correct UInt32\n");
#endif
    return LZMA_RESULT_DATA_ERROR;
  }

  {
    long length=s_len;
    if ((long)(SizeT)length != length)
    {
#if defined(DEBUG_ENABLE_BOOTSTRAP_PRINTF) || !defined(CFG_BOOTSTRAP_CODE)
      printf("Too big compressed stream\n");
#endif
      return LZMA_RESULT_DATA_ERROR;
    }
    compressedSize = (SizeT)(length - (LZMA_PROPERTIES_SIZE + 8));
  }

  /* Read LZMA properties for compressed stream */

  if (!MyReadFileAndCheck(source, properties, sizeof(properties)))
  {
#if defined(DEBUG_ENABLE_BOOTSTRAP_PRINTF) || !defined(CFG_BOOTSTRAP_CODE)
    printf("%s\n", kCantReadMessage);
#endif
    return LZMA_RESULT_DATA_ERROR;
  }

  /* Read uncompressed size */
  {
    int i;
    for (i = 0; i < 8; i++)
    {
      unsigned char b;
      if (!MyReadFileAndCheck(source, &b, 1))
      {
#if defined(DEBUG_ENABLE_BOOTSTRAP_PRINTF) || !defined(CFG_BOOTSTRAP_CODE)
        printf("%s\n", kCantReadMessage);
#endif
        return LZMA_RESULT_DATA_ERROR;
      }
      if (b != 0xFF)
        waitEOS = 0;
      if (i < 4)
        outSize += (UInt32)(b) << (i * 8);
      else
        outSizeHigh += (UInt32)(b) << ((i - 4) * 8);
    }
    
    if (waitEOS)
    {
#if defined(DEBUG_ENABLE_BOOTSTRAP_PRINTF) || !defined(CFG_BOOTSTRAP_CODE)
      printf("Stream with EOS marker is not supported");
#endif
      return LZMA_RESULT_DATA_ERROR;
    }
    outSizeFull = (SizeT)outSize;
    if (sizeof(SizeT) >= 8)
      outSizeFull |= (((SizeT)outSizeHigh << 16) << 16);
    else if (outSizeHigh != 0 || (UInt32)(SizeT)outSize != outSize)
    {
#if defined(DEBUG_ENABLE_BOOTSTRAP_PRINTF) || !defined(CFG_BOOTSTRAP_CODE)
      printf("Too big uncompressed stream");
#endif
      return LZMA_RESULT_DATA_ERROR;
    }
  }

  /* Decode LZMA properties and allocate memory */
  if (LzmaDecodeProperties(&state.Properties, properties, LZMA_PROPERTIES_SIZE) != LZMA_RESULT_OK)
  {
#if defined(DEBUG_ENABLE_BOOTSTRAP_PRINTF) || !defined(CFG_BOOTSTRAP_CODE)
    printf("Incorrect stream properties");
#endif
    return LZMA_RESULT_DATA_ERROR;
  }
  state.Probs = (CProb *)malloc(LzmaGetNumProbs(&state.Properties) * sizeof(CProb));

  if (outSizeFull == 0)
    outStream = 0;
  else
  {
    if (outSizeFull > *d_len)
      outStream = 0;
    else
      outStream = dest;
  }

  if (compressedSize == 0)
    inStream = 0;
  else
  {
    if ((compressedSize+rpos) > s_len )
      inStream = 0;
    else
      inStream = source + rpos;
  }

  if (state.Probs == 0 
    || (outStream == 0 && outSizeFull != 0)
    || (inStream == 0 && compressedSize != 0)
    )
  {
    free(state.Probs);
#if defined(DEBUG_ENABLE_BOOTSTRAP_PRINTF) || !defined(CFG_BOOTSTRAP_CODE)
    printf("%s\n", kCantAllocateMessage);
#endif
    return LZMA_RESULT_DATA_ERROR;
  }

  /* Decompress */
  {
    SizeT inProcessed;
    SizeT outProcessed;
    res = LzmaDecode(&state,
      inStream, compressedSize, &inProcessed,
      outStream, outSizeFull, &outProcessed);
    if (res != 0)
    {
#if defined(DEBUG_ENABLE_BOOTSTRAP_PRINTF) || !defined(CFG_BOOTSTRAP_CODE)
      printf("\nDecoding error = %d\n", res);
#endif
      res = 1;
    }
    else
    {
      *d_len = outProcessed;
    }
  }

  free(state.Probs);
  return res;
}