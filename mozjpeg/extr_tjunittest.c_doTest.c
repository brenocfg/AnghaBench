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
typedef  int /*<<< orphan*/ * tjhandle ;

/* Variables and functions */
 int TJFLAG_BOTTOMUP ; 
 int TJFLAG_FASTUPSAMPLE ; 
 int TJPF_RGBA ; 
 int TJPF_RGBX ; 
 int TJPF_XRGB ; 
 int TJSAMP_411 ; 
 int TJSAMP_420 ; 
 int TJSAMP_422 ; 
 int TJSAMP_440 ; 
 int /*<<< orphan*/  _throw (char*) ; 
 int /*<<< orphan*/  _throwtj () ; 
 int /*<<< orphan*/  alloc ; 
 int /*<<< orphan*/  compTest (int /*<<< orphan*/ *,unsigned char**,unsigned long*,int,int,int,char*,int,int,int) ; 
 int /*<<< orphan*/  decompTest (int /*<<< orphan*/ *,unsigned char*,unsigned long,int,int,int,char*,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ tjAlloc (unsigned long) ; 
 unsigned long tjBufSize (int,int,int) ; 
 int /*<<< orphan*/  tjDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tjFree (unsigned char*) ; 
 int /*<<< orphan*/ * tjInitCompress () ; 
 int /*<<< orphan*/ * tjInitDecompress () ; 

void doTest(int w, int h, const int *formats, int nformats, int subsamp,
            char *basename)
{
  tjhandle chandle = NULL, dhandle = NULL;
  unsigned char *dstBuf = NULL;
  unsigned long size = 0;
  int pfi, pf, i;

  if (!alloc)
    size = tjBufSize(w, h, subsamp);
  if (size != 0)
    if ((dstBuf = (unsigned char *)tjAlloc(size)) == NULL)
      _throw("Memory allocation failure.");

  if ((chandle = tjInitCompress()) == NULL ||
      (dhandle = tjInitDecompress()) == NULL)
    _throwtj();

  for (pfi = 0; pfi < nformats; pfi++) {
    for (i = 0; i < 2; i++) {
      int flags = 0;

      if (subsamp == TJSAMP_422 || subsamp == TJSAMP_420 ||
          subsamp == TJSAMP_440 || subsamp == TJSAMP_411)
        flags |= TJFLAG_FASTUPSAMPLE;
      if (i == 1) flags |= TJFLAG_BOTTOMUP;
      pf = formats[pfi];
      compTest(chandle, &dstBuf, &size, w, h, pf, basename, subsamp, 100,
               flags);
      decompTest(dhandle, dstBuf, size, w, h, pf, basename, subsamp, flags);
      if (pf >= TJPF_RGBX && pf <= TJPF_XRGB) {
        printf("\n");
        decompTest(dhandle, dstBuf, size, w, h, pf + (TJPF_RGBA - TJPF_RGBX),
                   basename, subsamp, flags);
      }
      printf("\n");
    }
  }
  printf("--------------------\n\n");

bailout:
  if (chandle) tjDestroy(chandle);
  if (dhandle) tjDestroy(dhandle);
  if (dstBuf) tjFree(dstBuf);
}