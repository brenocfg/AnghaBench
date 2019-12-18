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
struct TYPE_3__ {int L; int base; int* p; int num; int /*<<< orphan*/  pos; } ;
typedef  TYPE_1__ primegen ;

/* Variables and functions */
 int /*<<< orphan*/  PRIMEGEN_WORDS ; 

void primegen_init(primegen *pg)
{
  pg->L = 1;
  pg->base = 60;

  pg->pos = PRIMEGEN_WORDS;

  pg->p[0] = 59;
  pg->p[1] = 53;
  pg->p[2] = 47;
  pg->p[3] = 43;
  pg->p[4] = 41;
  pg->p[5] = 37;
  pg->p[6] = 31;
  pg->p[7] = 29;
  pg->p[8] = 23;
  pg->p[9] = 19;
  pg->p[10] = 17;
  pg->p[11] = 13;
  pg->p[12] = 11;
  pg->p[13] = 7;
  pg->p[14] = 5;
  pg->p[15] = 3;
  pg->p[16] = 2;

  pg->num = 17;
}