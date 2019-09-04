#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  preset_dict_size; int /*<<< orphan*/  preset_dict; int /*<<< orphan*/  depth; int /*<<< orphan*/  mf; int /*<<< orphan*/  nice_len; int /*<<< orphan*/  dict_size; } ;
typedef  TYPE_1__ lzma_options_lzma ;
struct TYPE_6__ {int /*<<< orphan*/  preset_dict_size; int /*<<< orphan*/  preset_dict; int /*<<< orphan*/  depth; int /*<<< orphan*/  match_finder; int /*<<< orphan*/  nice_len; int /*<<< orphan*/  match_len_max; int /*<<< orphan*/  after_size; int /*<<< orphan*/  dict_size; int /*<<< orphan*/  before_size; } ;
typedef  TYPE_2__ lzma_lz_options ;

/* Variables and functions */
 int /*<<< orphan*/  LOOP_INPUT_MAX ; 
 int /*<<< orphan*/  MATCH_LEN_MAX ; 
 int /*<<< orphan*/  OPTS ; 

__attribute__((used)) static void
set_lz_options(lzma_lz_options *lz_options, const lzma_options_lzma *options)
{
	// LZ encoder initialization does the validation for these so we
	// don't need to validate here.
	lz_options->before_size = OPTS;
	lz_options->dict_size = options->dict_size;
	lz_options->after_size = LOOP_INPUT_MAX;
	lz_options->match_len_max = MATCH_LEN_MAX;
	lz_options->nice_len = options->nice_len;
	lz_options->match_finder = options->mf;
	lz_options->depth = options->depth;
	lz_options->preset_dict = options->preset_dict;
	lz_options->preset_dict_size = options->preset_dict_size;
	return;
}