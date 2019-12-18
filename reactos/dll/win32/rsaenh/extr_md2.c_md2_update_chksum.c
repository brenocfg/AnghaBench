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
struct TYPE_3__ {unsigned char* chksum; unsigned char* buf; } ;
typedef  TYPE_1__ md2_state ;

/* Variables and functions */
 int* PI_SUBST ; 

__attribute__((used)) static void md2_update_chksum(md2_state *md2)
{
   int j;
   unsigned char L;
   L = md2->chksum[15];
   for (j = 0; j < 16; j++) {

/* caution, the RFC says its "C[j] = S[M[i*16+j] xor L]" but the reference source code [and test vectors] say 
   otherwise.
*/
       L = (md2->chksum[j] ^= PI_SUBST[(int)(md2->buf[j] ^ L)] & 255);
   }
}