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
struct TYPE_3__ {int /*<<< orphan*/  buf_inc; } ;
typedef  TYPE_1__ RAsmOp ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_buf_new_with_string (char*) ; 
 char* r_file_slurp (char*,int*) ; 
 scalar_t__ r_num_math (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_replace_char (char*,char,char) ; 
 int /*<<< orphan*/  r_str_word_get0 (char*,int) ; 
 int /*<<< orphan*/  r_str_word_set0 (char*) ; 

__attribute__((used)) static inline int r_asm_pseudo_incbin(RAsmOp *op, char *input) {
	int bytes_read = 0;
	r_str_replace_char (input, ',', ' ');
	// int len = r_str_word_count (input);
	r_str_word_set0 (input);
	//const char *filename = r_str_word_get0 (input, 0);
	int skip = (int)r_num_math (NULL, r_str_word_get0 (input, 1));
	int count = (int)r_num_math (NULL,r_str_word_get0 (input, 2));
	char *content = r_file_slurp (input, &bytes_read);
	if (skip > 0) {
		skip = skip > bytes_read ? bytes_read : skip;
	}
	if (count > 0) {
		count = count > bytes_read ? 0 : count;
	} else {
		count = bytes_read;
	}
	// Need to handle arbitrary amount of data
	r_buf_free (op->buf_inc);
	op->buf_inc = r_buf_new_with_string (content + skip);
	// Terminate the original buffer
	free (content);
	return count;
}