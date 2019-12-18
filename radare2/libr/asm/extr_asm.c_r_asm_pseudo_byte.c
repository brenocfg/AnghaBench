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
typedef  int ut8 ;
typedef  int /*<<< orphan*/  RAsmOp ;

/* Variables and functions */
 int /*<<< orphan*/  free (int*) ; 
 int* malloc (int) ; 
 int /*<<< orphan*/  r_asm_op_set_buf (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ r_num_math (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  r_str_replace_char (char*,char,char) ; 
 int r_str_word_count (char*) ; 
 char* r_str_word_get0 (char*,int) ; 
 int /*<<< orphan*/  r_str_word_set0 (char*) ; 

__attribute__((used)) static inline int r_asm_pseudo_byte(RAsmOp *op, char *input) {
	int i, len = 0;
	r_str_replace_char (input, ',', ' ');
	len = r_str_word_count (input);
	r_str_word_set0 (input);
	ut8 *buf = malloc (len);
	if (!buf) {
		return 0;
	}
	for (i = 0; i < len; i++) {
		const char *word = r_str_word_get0 (input, i);
		int num = (int)r_num_math (NULL, word);
		buf[i] = num;
	}
	r_asm_op_set_buf (op, buf, len);
	free (buf);
	return len;
}