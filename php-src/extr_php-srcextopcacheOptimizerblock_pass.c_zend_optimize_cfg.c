#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_uchar ;
struct TYPE_29__ {int debug_level; int /*<<< orphan*/  arena; } ;
typedef  TYPE_1__ zend_optimizer_ctx ;
struct TYPE_30__ {int last_var; int T; } ;
typedef  TYPE_2__ zend_op_array ;
typedef  int /*<<< orphan*/  zend_op ;
struct TYPE_31__ {int blocks_count; TYPE_4__* blocks; } ;
typedef  TYPE_3__ zend_cfg ;
typedef  int /*<<< orphan*/ * zend_bitset ;
struct TYPE_32__ {int flags; } ;
typedef  TYPE_4__ zend_basic_block ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int PASSES ; 
 scalar_t__ SUCCESS ; 
 int ZEND_BB_FOLLOW ; 
 int ZEND_BB_REACHABLE ; 
 int ZEND_BB_TARGET ; 
 scalar_t__ ZEND_BITSET_ELM_SIZE ; 
 int ZEND_DUMP_AFTER_BLOCK_PASS ; 
 int ZEND_DUMP_BEFORE_BLOCK_PASS ; 
 int ZEND_DUMP_CFG ; 
 int ZEND_DUMP_HIDE_UNREACHABLE ; 
 int /*<<< orphan*/  assemble_code_blocks (TYPE_3__*,TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strip_nops (TYPE_2__*,TYPE_4__*) ; 
 void* zend_arena_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ ** zend_arena_calloc (int /*<<< orphan*/ *,int,int) ; 
 void* zend_arena_checkpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_arena_release (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  zend_bitset_clear (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ zend_bitset_len (int) ; 
 scalar_t__ zend_build_cfg (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  zend_cfg_remark_reachable_blocks (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  zend_dump_op_array (TYPE_2__*,int,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  zend_jmp_optimization (TYPE_4__*,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  zend_merge_blocks (TYPE_2__*,TYPE_3__*,scalar_t__*) ; 
 int /*<<< orphan*/  zend_optimize_block (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  zend_t_usage (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 

void zend_optimize_cfg(zend_op_array *op_array, zend_optimizer_ctx *ctx)
{
	zend_cfg cfg;
	zend_basic_block *blocks, *end, *b;
	int pass;
	uint32_t bitset_len;
	zend_bitset usage;
	void *checkpoint;
	zend_op **Tsource;
	zend_uchar *same_t;
	uint32_t opt_count;

    /* Build CFG */
	checkpoint = zend_arena_checkpoint(ctx->arena);
	if (zend_build_cfg(&ctx->arena, op_array, 0, &cfg) != SUCCESS) {
		zend_arena_release(&ctx->arena, checkpoint);
		return;
	}

	if (cfg.blocks_count * (op_array->last_var + op_array->T) > 64 * 1024 * 1024) {
		zend_arena_release(&ctx->arena, checkpoint);
		return;
	}

	if (ctx->debug_level & ZEND_DUMP_BEFORE_BLOCK_PASS) {
		zend_dump_op_array(op_array, ZEND_DUMP_CFG, "before block pass", &cfg);
	}

	if (op_array->last_var || op_array->T) {
		bitset_len = zend_bitset_len(op_array->last_var + op_array->T);
		Tsource = zend_arena_calloc(&ctx->arena, op_array->last_var + op_array->T, sizeof(zend_op *));
		same_t = zend_arena_alloc(&ctx->arena, op_array->last_var + op_array->T);
		usage = zend_arena_alloc(&ctx->arena, bitset_len * ZEND_BITSET_ELM_SIZE);
	} else {
		bitset_len = 0;
		Tsource = NULL;
		same_t = NULL;
		usage = NULL;
	}
	blocks = cfg.blocks;
	end = blocks + cfg.blocks_count;
	for (pass = 0; pass < PASSES; pass++) {
		opt_count = 0;

		/* Compute data dependencies */
		zend_bitset_clear(usage, bitset_len);
		zend_t_usage(&cfg, op_array, usage, ctx);

		/* optimize each basic block separately */
		for (b = blocks; b < end; b++) {
			if (!(b->flags & ZEND_BB_REACHABLE)) {
				continue;
			}
			/* we track data dependencies only insight a single basic block */
			if (!(b->flags & ZEND_BB_FOLLOW) ||
			    (b->flags & ZEND_BB_TARGET)) {
				/* Skip continuation of "extended" BB */
				memset(Tsource, 0, (op_array->last_var + op_array->T) * sizeof(zend_op *));
			}
			zend_optimize_block(b, op_array, usage, &cfg, Tsource, &opt_count);
		}

		/* Eliminate NOPs */
		for (b = blocks; b < end; b++) {
			if (b->flags & ZEND_BB_REACHABLE) {
				strip_nops(op_array, b);
			}
		}

		/* Jump optimization for each block */
		for (b = blocks; b < end; b++) {
			if (b->flags & ZEND_BB_REACHABLE) {
				zend_jmp_optimization(b, op_array, &cfg, same_t, &opt_count);
			}
		}

		/* Eliminate unreachable basic blocks */
		zend_cfg_remark_reachable_blocks(op_array, &cfg);

		/* Merge Blocks */
		zend_merge_blocks(op_array, &cfg, &opt_count);

		if (opt_count == 0) {
			break;
		}
	}

	zend_bitset_clear(usage, bitset_len);
	zend_t_usage(&cfg, op_array, usage, ctx);
	assemble_code_blocks(&cfg, op_array, ctx);

	if (ctx->debug_level & ZEND_DUMP_AFTER_BLOCK_PASS) {
		zend_dump_op_array(op_array, ZEND_DUMP_CFG | ZEND_DUMP_HIDE_UNREACHABLE, "after block pass", &cfg);
	}

	/* Destroy CFG */
	zend_arena_release(&ctx->arena, checkpoint);
}