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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  unsigned short u16 ;
typedef  int sint ;

/* Variables and functions */
 unsigned short Hi16 (int /*<<< orphan*/ ) ; 
 unsigned short Lo16 (int /*<<< orphan*/ ) ; 
 unsigned short Mk16 (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int PHASE1_LOOP_CNT ; 
 unsigned short TK16 (int) ; 
 scalar_t__ _S_ (unsigned short) ; 

__attribute__((used)) static void phase1(u16 *p1k, const u8 *tk, const u8 *ta, u32 iv32)
{
	sint  i;

	/* Initialize the 80 bits of P1K[] from IV32 and TA[0..5]     */
	p1k[0] = Lo16(iv32);
	p1k[1] = Hi16(iv32);
	p1k[2] = Mk16(ta[1], ta[0]); /* use TA[] as little-endian */
	p1k[3] = Mk16(ta[3], ta[2]);
	p1k[4] = Mk16(ta[5], ta[4]);
	/* Now compute an unbalanced Feistel cipher with 80-bit block */
	/* size on the 80-bit block P1K[], using the 128-bit key TK[] */
	for (i = 0; i < PHASE1_LOOP_CNT; i++) {  /* Each add is mod 2**16 */
		p1k[0] += _S_(p1k[4] ^ TK16((i & 1) + 0));
		p1k[1] += _S_(p1k[0] ^ TK16((i & 1) + 2));
		p1k[2] += _S_(p1k[1] ^ TK16((i & 1) + 4));
		p1k[3] += _S_(p1k[2] ^ TK16((i & 1) + 6));
		p1k[4] += _S_(p1k[3] ^ TK16((i & 1) + 0));
		p1k[4] +=  (unsigned short)i;	/* avoid "slide attacks" */
	}
}