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
struct nios2_opcode {unsigned long match; unsigned long mask; } ;
struct TYPE_4__ {struct nios2_opcode const* opcode; struct TYPE_4__* next; } ;
typedef  TYPE_1__ nios2_opcode_hash ;

/* Variables and functions */
 unsigned long OP_MASK_OP ; 
 unsigned long OP_SH_OP ; 
 TYPE_1__** nios2_hash ; 
 int /*<<< orphan*/  nios2_hash_init ; 
 int /*<<< orphan*/  nios2_init_opcode_hash () ; 
 TYPE_1__** nios2_ps_hash ; 

const struct nios2_opcode *
nios2_find_opcode_hash (unsigned long opcode)
{
  nios2_opcode_hash *entry;

  /* Build a hash table to shorten the search time.  */
  if (!nios2_hash_init) {
	  nios2_init_opcode_hash ();
  }

  /* First look in the pseudo-op hashtable.  */
  for (entry = nios2_ps_hash[(opcode >> OP_SH_OP) & OP_MASK_OP];
	  entry; entry = entry->next) {
	  if (entry->opcode->match == (opcode & entry->opcode->mask)) {
		  return entry->opcode;
	  }
  }

  /* Otherwise look in the main hashtable.  */
  for (entry = nios2_hash[(opcode >> OP_SH_OP) & OP_MASK_OP];
	  entry; entry = entry->next) {
	  if (entry->opcode->match == (opcode & entry->opcode->mask)) {
		  return entry->opcode;
	  }
  }

  return NULL;
}