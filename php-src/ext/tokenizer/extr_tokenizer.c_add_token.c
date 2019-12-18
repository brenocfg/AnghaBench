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
typedef  int /*<<< orphan*/  zval ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTR_CHAR (unsigned char) ; 
 int /*<<< orphan*/  add_next_index_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_next_index_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_next_index_stringl (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_token(zval *return_value, int token_type,
		unsigned char *text, size_t leng, int lineno) {
	if (token_type >= 256) {
		zval keyword;
		array_init(&keyword);
		add_next_index_long(&keyword, token_type);
		if (leng == 1) {
			add_next_index_str(&keyword, ZSTR_CHAR(text[0]));
		} else {
			add_next_index_stringl(&keyword, (char *) text, leng);
		}
		add_next_index_long(&keyword, lineno);
		add_next_index_zval(return_value, &keyword);
	} else {
		if (leng == 1) {
			add_next_index_str(return_value, ZSTR_CHAR(text[0]));
		} else {
			add_next_index_stringl(return_value, (char *) text, leng);
		}
	}
}