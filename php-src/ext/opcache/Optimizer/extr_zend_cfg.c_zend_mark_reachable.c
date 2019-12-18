#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zend_uchar ;
struct TYPE_7__ {scalar_t__ opcode; } ;
typedef  TYPE_1__ zend_op ;
struct TYPE_8__ {int flags; TYPE_3__* blocks; } ;
typedef  TYPE_2__ zend_cfg ;
struct TYPE_9__ {int flags; int successors_count; int* successors; int len; int start; } ;
typedef  TYPE_3__ zend_basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ASSERT (int) ; 
 int ZEND_BB_ENTRY ; 
 int ZEND_BB_EXIT ; 
 int ZEND_BB_FOLLOW ; 
 int ZEND_BB_REACHABLE ; 
 int ZEND_BB_RECV_ENTRY ; 
 int ZEND_BB_TARGET ; 
 int ZEND_CFG_RECV_ENTRY ; 
 int ZEND_CFG_STACKLESS ; 
 scalar_t__ ZEND_DO_FCALL ; 
 scalar_t__ ZEND_DO_FCALL_BY_NAME ; 
 scalar_t__ ZEND_DO_UCALL ; 
 scalar_t__ ZEND_GENERATOR_CREATE ; 
 scalar_t__ ZEND_INCLUDE_OR_EVAL ; 
 scalar_t__ ZEND_JMP ; 
 scalar_t__ ZEND_JMPZNZ ; 
 scalar_t__ ZEND_RECV ; 
 scalar_t__ ZEND_RECV_INIT ; 
 scalar_t__ ZEND_SWITCH_LONG ; 
 scalar_t__ ZEND_SWITCH_STRING ; 
 scalar_t__ ZEND_YIELD ; 
 scalar_t__ ZEND_YIELD_FROM ; 

__attribute__((used)) static void zend_mark_reachable(zend_op *opcodes, zend_cfg *cfg, zend_basic_block *b) /* {{{ */
{
	zend_basic_block *blocks = cfg->blocks;

	while (1) {
		int i;

		b->flags |= ZEND_BB_REACHABLE;
		if (b->successors_count == 0) {
			b->flags |= ZEND_BB_EXIT;
			return;
		}

		for (i = 0; i < b->successors_count; i++) {
			zend_basic_block *succ = blocks + b->successors[i];

			if (b->len != 0) {
				zend_uchar opcode = opcodes[b->start + b->len - 1].opcode;
				if (b->successors_count == 1) {
					if (opcode == ZEND_JMP) {
						succ->flags |= ZEND_BB_TARGET;
					} else {
						succ->flags |= ZEND_BB_FOLLOW;

						if ((cfg->flags & ZEND_CFG_STACKLESS)) {
							if (opcode == ZEND_INCLUDE_OR_EVAL ||
								opcode == ZEND_GENERATOR_CREATE ||
								opcode == ZEND_YIELD ||
								opcode == ZEND_YIELD_FROM ||
								opcode == ZEND_DO_FCALL ||
								opcode == ZEND_DO_UCALL ||
								opcode == ZEND_DO_FCALL_BY_NAME) {
								succ->flags |= ZEND_BB_ENTRY;
							}
						}
						if ((cfg->flags & ZEND_CFG_RECV_ENTRY)) {
							if (opcode == ZEND_RECV ||
								opcode == ZEND_RECV_INIT) {
								succ->flags |= ZEND_BB_RECV_ENTRY;
							}
						}
					}
				} else if (b->successors_count == 2) {
					if (i == 0 || opcode == ZEND_JMPZNZ) {
						succ->flags |= ZEND_BB_TARGET;
					} else {
						succ->flags |= ZEND_BB_FOLLOW;
					}
				} else {
					ZEND_ASSERT(opcode == ZEND_SWITCH_LONG || opcode == ZEND_SWITCH_STRING);
					if (i == b->successors_count - 1) {
						succ->flags |= ZEND_BB_FOLLOW | ZEND_BB_TARGET;
					} else {
						succ->flags |= ZEND_BB_TARGET;
					}
				}
			} else {
				succ->flags |= ZEND_BB_FOLLOW;
			}

			if (i == b->successors_count - 1) {
				/* Tail call optimization */
				if (succ->flags & ZEND_BB_REACHABLE) {
					return;
				}

				b = succ;
				break;
			} else {
				/* Recusively check reachability */
				if (!(succ->flags & ZEND_BB_REACHABLE)) {
					zend_mark_reachable(opcodes, cfg, succ);
				}
			}
		}
	}
}