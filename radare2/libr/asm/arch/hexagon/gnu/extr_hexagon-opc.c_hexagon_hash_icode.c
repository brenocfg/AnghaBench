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
typedef  int hexagon_hash ;

/* Variables and functions */
 int const HEXAGON_END_PACKET_GET (int) ; 
 int const HEXAGON_END_PACKET_MASK ; 
 int const HEXAGON_END_PACKET_POS ; 
 int HEXAGON_INSN_LEN ; 
 int const hexagon_icode_hash_bits ; 

hexagon_hash
hexagon_hash_icode
(hexagon_insn insn)
{
  const hexagon_hash xtra = ~(-(HEXAGON_END_PACKET_MASK >> HEXAGON_END_PACKET_POS));
  hexagon_hash hash;

  hash  = insn >> (HEXAGON_INSN_LEN * 8 - (hexagon_icode_hash_bits - xtra));
  hash |= (HEXAGON_END_PACKET_GET (insn) >> HEXAGON_END_PACKET_POS)
          << (hexagon_icode_hash_bits - xtra);

  return (hash);
}