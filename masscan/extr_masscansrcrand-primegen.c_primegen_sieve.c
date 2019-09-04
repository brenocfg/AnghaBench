#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int** buf; int L; } ;
typedef  TYPE_1__ primegen ;
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {scalar_t__ k; int /*<<< orphan*/  g; int /*<<< orphan*/  f; } ;
struct TYPE_8__ {scalar_t__ k; int /*<<< orphan*/  g; int /*<<< orphan*/  f; } ;
struct TYPE_7__ {scalar_t__ k; int /*<<< orphan*/  g; int /*<<< orphan*/  f; } ;

/* Variables and functions */
 int B32 ; 
 int /*<<< orphan*/  clear (int**) ; 
 int /*<<< orphan*/  doit12 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  doit4 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  doit6 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_5__* for12 ; 
 TYPE_4__* for4 ; 
 TYPE_3__* for6 ; 
 int* qqtab ; 
 int /*<<< orphan*/  squarefree1 (int**,int,int) ; 
 int /*<<< orphan*/  squarefree49 (int**,int,int) ; 
 int /*<<< orphan*/  squarefreetiny (int*,int*,int) ; 

void primegen_sieve(primegen *pg)
{
  uint32_t (*buf)[B32];
  uint64_t L;
  int i;
  uint32_t Lmodqq[49];

  buf = pg->buf;
  L = pg->L;

  if (L > 2000000000)
    for (i = 0;i < 49;++i)
      Lmodqq[i] = L % qqtab[i];
  else
    for (i = 0;i < 49;++i)
      Lmodqq[i] = ((uint32_t) L) % qqtab[i];

  clear(buf);

  for (i = 0;i < 16;++i)
    doit4(buf[0],for4[i].f,for4[i].g,(int64_t) for4[i].k - L);
  squarefreetiny(buf[0],Lmodqq,1);
  for (;i < 32;++i)
    doit4(buf[3],for4[i].f,for4[i].g,(int64_t) for4[i].k - L);
  squarefreetiny(buf[3],Lmodqq,13);
  for (;i < 48;++i)
    doit4(buf[4],for4[i].f,for4[i].g,(int64_t) for4[i].k - L);
  squarefreetiny(buf[4],Lmodqq,17);
  for (;i < 64;++i)
    doit4(buf[7],for4[i].f,for4[i].g,(int64_t) for4[i].k - L);
  squarefreetiny(buf[7],Lmodqq,29);
  for (;i < 80;++i)
    doit4(buf[9],for4[i].f,for4[i].g,(int64_t) for4[i].k - L);
  squarefreetiny(buf[9],Lmodqq,37);
  for (;i < 96;++i)
    doit4(buf[10],for4[i].f,for4[i].g,(int64_t) for4[i].k - L);
  squarefreetiny(buf[10],Lmodqq,41);
  for (;i < 112;++i)
    doit4(buf[13],for4[i].f,for4[i].g,(int64_t) for4[i].k - L);
  squarefreetiny(buf[13],Lmodqq,49);
  for (;i < 128;++i)
    doit4(buf[14],for4[i].f,for4[i].g,(int64_t) for4[i].k - L);
  squarefreetiny(buf[14],Lmodqq,53);

  for (i = 0;i < 12;++i)
    doit6(buf[1],for6[i].f,for6[i].g,(int64_t) for6[i].k - L);
  squarefreetiny(buf[1],Lmodqq,7);
  for (;i < 24;++i)
    doit6(buf[5],for6[i].f,for6[i].g,(int64_t) for6[i].k - L);
  squarefreetiny(buf[5],Lmodqq,19);
  for (;i < 36;++i)
    doit6(buf[8],for6[i].f,for6[i].g,(int64_t) for6[i].k - L);
  squarefreetiny(buf[8],Lmodqq,31);
  for (;i < 48;++i)
    doit6(buf[11],for6[i].f,for6[i].g,(int64_t) for6[i].k - L);
  squarefreetiny(buf[11],Lmodqq,43);

  for (i = 0;i < 24;++i)
    doit12(buf[2],for12[i].f,for12[i].g,(int64_t) for12[i].k - L);
  squarefreetiny(buf[2],Lmodqq,11);
  for (;i < 48;++i)
    doit12(buf[6],for12[i].f,for12[i].g,(int64_t) for12[i].k - L);
  squarefreetiny(buf[6],Lmodqq,23);
  for (;i < 72;++i)
    doit12(buf[12],for12[i].f,for12[i].g,(int64_t) for12[i].k - L);
  squarefreetiny(buf[12],Lmodqq,47);
  for (;i < 96;++i)
    doit12(buf[15],for12[i].f,for12[i].g,(int64_t) for12[i].k - L);
  squarefreetiny(buf[15],Lmodqq,59);

  squarefree49(buf,L,247);
  squarefree49(buf,L,253);
  squarefree49(buf,L,257);
  squarefree49(buf,L,263);
  squarefree1(buf,L,241);
  squarefree1(buf,L,251);
  squarefree1(buf,L,259);
  squarefree1(buf,L,269);
}