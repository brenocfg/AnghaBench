#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lzma_ret ;
struct TYPE_8__ {scalar_t__ lc; scalar_t__ lp; scalar_t__ pb; } ;
typedef  TYPE_2__ lzma_options_lzma ;
struct TYPE_9__ {TYPE_2__* options; } ;
typedef  TYPE_3__ lzma_filter ;
struct TYPE_7__ {scalar_t__ lc; scalar_t__ lp; scalar_t__ pb; } ;
struct TYPE_10__ {scalar_t__ sequence; int need_properties; int need_state_reset; TYPE_1__ opt_cur; } ;
typedef  TYPE_4__ lzma_coder ;

/* Variables and functions */
 scalar_t__ LZMA_LCLP_MAX ; 
 int /*<<< orphan*/  LZMA_OK ; 
 int /*<<< orphan*/  LZMA_OPTIONS_ERROR ; 
 scalar_t__ LZMA_PB_MAX ; 
 int /*<<< orphan*/  LZMA_PROG_ERROR ; 
 scalar_t__ SEQ_INIT ; 

__attribute__((used)) static lzma_ret
lzma2_encoder_options_update(lzma_coder *coder, const lzma_filter *filter)
{
	// New options can be set only when there is no incomplete chunk.
	// This is the case at the beginning of the raw stream and right
	// after LZMA_SYNC_FLUSH.
	if (filter->options == NULL || coder->sequence != SEQ_INIT)
		return LZMA_PROG_ERROR;

	// Look if there are new options. At least for now,
	// only lc/lp/pb can be changed.
	const lzma_options_lzma *opt = filter->options;
	if (coder->opt_cur.lc != opt->lc || coder->opt_cur.lp != opt->lp
			|| coder->opt_cur.pb != opt->pb) {
		// Validate the options.
		if (opt->lc > LZMA_LCLP_MAX || opt->lp > LZMA_LCLP_MAX
				|| opt->lc + opt->lp > LZMA_LCLP_MAX
				|| opt->pb > LZMA_PB_MAX)
			return LZMA_OPTIONS_ERROR;

		// The new options will be used when the encoder starts
		// a new LZMA2 chunk.
		coder->opt_cur.lc = opt->lc;
		coder->opt_cur.lp = opt->lp;
		coder->opt_cur.pb = opt->pb;
		coder->need_properties = true;
		coder->need_state_reset = true;
	}

	return LZMA_OK;
}