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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HEXAGON_END_NOT ; 
 int HEXAGON_END_PACKET_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEXAGON_END_PAIR ; 
 int HEXAGON_INSN_LEN ; 
 scalar_t__ ISSPACE (char const) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

hexagon_insn
hexagon_encode_opcode
(const char *enc)
{
  hexagon_insn insn;
  int num_bits;
  int pair;

  for (insn = 0, num_bits = 0, pair = 0; *enc; enc++)
    {
      while (ISSPACE (*enc))
        enc++;

      if (!*enc)
        break;

      insn = (insn << 1) + ((*enc == '1')? 1: 0);

      num_bits++;

      pair |= ((enc [0] == 'E' && enc [1] == 'E'));
    }

  if (num_bits != HEXAGON_INSN_LEN * 8)
    {
      printf ("invalid number of bits: %d\n", num_bits);
      assert (FALSE);
    }

  return (HEXAGON_END_PACKET_SET (insn, pair? HEXAGON_END_PAIR: HEXAGON_END_NOT));
}