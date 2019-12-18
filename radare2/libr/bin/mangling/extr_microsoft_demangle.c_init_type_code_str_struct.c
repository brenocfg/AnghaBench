#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type_str_len; char* type_str; scalar_t__ curr_pos; } ;
typedef  TYPE_1__ STypeCodeStr ;

/* Variables and functions */
 int TYPE_STR_LEN ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_type_code_str_struct(STypeCodeStr *type_coder_str) {
#define TYPE_STR_LEN 1024
	// 1 - initialization finish with success, else - 0

	type_coder_str->type_str_len = TYPE_STR_LEN;

	type_coder_str->type_str = (char *) calloc (TYPE_STR_LEN, sizeof (char));
	if (!type_coder_str->type_str) {
		return 0;
	}
	memset (type_coder_str->type_str, 0, TYPE_STR_LEN * sizeof(char));

	type_coder_str->curr_pos = 0; // strlen ("unknown type");
//	strncpy(type_coder_str->type_str, "unknown_type", type_coder_str->curr_pos);

	return 1;
#undef TYPE_STR_LEN
}