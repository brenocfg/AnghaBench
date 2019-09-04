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
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
expand_fp_imm (int size, uint32_t imm8)
{
  uint64_t imm = 0;
  uint32_t imm8_7, imm8_6_0, imm8_6, imm8_6_repl4;

  imm8_7 = (imm8 >> 7) & 0x01;	/* imm8<7>   */
  imm8_6_0 = imm8 & 0x7f;	/* imm8<6:0> */
  imm8_6 = imm8_6_0 >> 6;	/* imm8<6>   */
  imm8_6_repl4 = (imm8_6 << 3) | (imm8_6 << 2)
    | (imm8_6 << 1) | imm8_6;	/* Replicate(imm8<6>,4) */
  if (size == 8)
    {
      imm = (imm8_7 << (63-32))		/* imm8<7>  */
	| ((imm8_6 ^ 1) << (62-32))	/* NOT(imm8<6)	*/
	| (imm8_6_repl4 << (58-32)) | (imm8_6 << (57-32))
	| (imm8_6 << (56-32)) | (imm8_6 << (55-32)) /* Replicate(imm8<6>,7) */
	| (imm8_6_0 << (48-32));	/* imm8<6>:imm8<5:0>    */
      imm <<= 32;
    }
  else if (size == 4 || size == 2)
    {
      imm = (imm8_7 << 31)	/* imm8<7>              */
	| ((imm8_6 ^ 1) << 30)	/* NOT(imm8<6>)         */
	| (imm8_6_repl4 << 26)	/* Replicate(imm8<6>,4) */
	| (imm8_6_0 << 19);	/* imm8<6>:imm8<5:0>    */
    }
  else
    {
      /* An unsupported size.  */
      assert (0);
    }

  return imm;
}