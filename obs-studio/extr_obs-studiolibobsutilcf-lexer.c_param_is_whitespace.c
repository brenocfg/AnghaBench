#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t num; struct cf_token* array; } ;
struct macro_param {TYPE_1__ tokens; } ;
struct cf_token {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CFTOKEN_NEWLINE ; 
 scalar_t__ CFTOKEN_NONE ; 
 scalar_t__ CFTOKEN_SPACETAB ; 

__attribute__((used)) static inline bool param_is_whitespace(const struct macro_param *param)
{
	struct cf_token *array = param->tokens.array;
	size_t i;

	for (i = 0; i < param->tokens.num; i++)
		if (array[i].type != CFTOKEN_NONE &&
		    array[i].type != CFTOKEN_SPACETAB &&
		    array[i].type != CFTOKEN_NEWLINE)
			return false;

	return true;
}