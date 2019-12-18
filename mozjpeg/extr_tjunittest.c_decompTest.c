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
struct TYPE_4__ {int num; int denom; } ;
typedef  TYPE_1__ tjscalingfactor ;
typedef  int /*<<< orphan*/  tjhandle ;

/* Variables and functions */
 int TJSAMP_411 ; 
 int TJSAMP_444 ; 
 int TJSAMP_GRAY ; 
 int /*<<< orphan*/  _decompTest (int /*<<< orphan*/ ,unsigned char*,unsigned long,int,int,int,char*,int,int,TYPE_1__) ; 
 int /*<<< orphan*/  _throwtj () ; 
 TYPE_1__* tjGetScalingFactors (int*) ; 

void decompTest(tjhandle handle, unsigned char *jpegBuf,
                unsigned long jpegSize, int w, int h, int pf, char *basename,
                int subsamp, int flags)
{
  int i, n = 0;
  tjscalingfactor *sf = tjGetScalingFactors(&n);

  if (!sf || !n) _throwtj();

  for (i = 0; i < n; i++) {
    if (subsamp == TJSAMP_444 || subsamp == TJSAMP_GRAY ||
        (subsamp == TJSAMP_411 && sf[i].num == 1 &&
         (sf[i].denom == 2 || sf[i].denom == 1)) ||
        (subsamp != TJSAMP_411 && sf[i].num == 1 &&
         (sf[i].denom == 4 || sf[i].denom == 2 || sf[i].denom == 1)))
      _decompTest(handle, jpegBuf, jpegSize, w, h, pf, basename, subsamp,
                  flags, sf[i]);
  }

bailout:
  return;
}