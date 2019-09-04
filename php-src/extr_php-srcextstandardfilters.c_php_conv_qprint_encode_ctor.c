#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dtor; scalar_t__ convert_op; } ;
struct TYPE_5__ {unsigned int line_ccnt; unsigned int line_len; char const* lbchars; size_t lbchars_len; int lbchars_dup; int persistent; int opts; scalar_t__ lb_ptr; scalar_t__ lb_cnt; TYPE_1__ _super; } ;
typedef  TYPE_2__ php_conv_qprint_encode ;
typedef  int /*<<< orphan*/  php_conv_err_t ;
typedef  scalar_t__ php_conv_dtor_func ;
typedef  scalar_t__ php_conv_convert_func ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_CONV_ERR_SUCCESS ; 
 int /*<<< orphan*/  PHP_CONV_ERR_TOO_BIG ; 
 char const* pestrdup (char const*,int) ; 
 scalar_t__ php_conv_qprint_encode_convert ; 
 scalar_t__ php_conv_qprint_encode_dtor ; 

__attribute__((used)) static php_conv_err_t php_conv_qprint_encode_ctor(php_conv_qprint_encode *inst, unsigned int line_len, const char *lbchars, size_t lbchars_len, int lbchars_dup, int opts, int persistent)
{
	if (line_len < 4 && lbchars != NULL) {
		return PHP_CONV_ERR_TOO_BIG;
	}
	inst->_super.convert_op = (php_conv_convert_func) php_conv_qprint_encode_convert;
	inst->_super.dtor = (php_conv_dtor_func) php_conv_qprint_encode_dtor;
	inst->line_ccnt = line_len;
	inst->line_len = line_len;
	if (lbchars != NULL) {
		inst->lbchars = (lbchars_dup ? pestrdup(lbchars, persistent) : lbchars);
		inst->lbchars_len = lbchars_len;
	} else {
		inst->lbchars = NULL;
	}
	inst->lbchars_dup = lbchars_dup;
	inst->persistent = persistent;
	inst->opts = opts;
	inst->lb_cnt = inst->lb_ptr = 0;
	return PHP_CONV_ERR_SUCCESS;
}