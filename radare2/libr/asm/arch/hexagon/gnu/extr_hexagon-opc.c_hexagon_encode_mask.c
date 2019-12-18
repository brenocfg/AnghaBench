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
typedef  int hexagon_insn ;

/* Variables and functions */
 int HEXAGON_INSN_LEN ; 
 scalar_t__ ISSPACE (char) ; 
 int /*<<< orphan*/  assert (int) ; 

hexagon_insn
hexagon_encode_mask
(char *enc)
{
  hexagon_insn mask;
  int num_bits;

  for (mask = 0, num_bits = 0; *enc; enc++)
    {
      while (ISSPACE (*enc))
        enc++;

      if (!*enc)
        break;

      mask = (mask << 1) + ((*enc == '1' || *enc == '0')? 1: 0);

      num_bits++;
    }

  assert (num_bits == HEXAGON_INSN_LEN * 8);
  return (mask);
}