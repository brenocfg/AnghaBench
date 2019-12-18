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
typedef  int zend_php_scanner_event ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int CG (int /*<<< orphan*/ ) ; 
 int END ; 
 int /*<<< orphan*/  IS_ARRAY ; 
 int LANG_SCNG (int /*<<< orphan*/ ) ; 
#define  ON_FEEDBACK 130 
#define  ON_STOP 129 
#define  ON_TOKEN 128 
 int T_CLOSE_TAG ; 
 int T_ECHO ; 
 int T_INLINE_HTML ; 
 int T_OPEN_TAG_WITH_ECHO ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_token (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  yy_cursor ; 
 int /*<<< orphan*/  yy_leng ; 
 int /*<<< orphan*/  yy_limit ; 
 int /*<<< orphan*/  yy_text ; 
 int /*<<< orphan*/ * zend_hash_index_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_hash_num_elements (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_lineno ; 

void on_event(zend_php_scanner_event event, int token, int line, void *context)
{
	zval *token_stream = (zval *) context;
	HashTable *tokens_ht;
	zval *token_zv;

	switch (event) {
		case ON_TOKEN:
			{
				if (token == END) break;
				/* Special cases */
				if (token == ';' && LANG_SCNG(yy_leng) > 1) { /* ?> or ?>\n or ?>\r\n */
					token = T_CLOSE_TAG;
				} else if (token == T_ECHO && LANG_SCNG(yy_leng) == sizeof("<?=") - 1) {
					token = T_OPEN_TAG_WITH_ECHO;
				}
				add_token(token_stream, token, LANG_SCNG(yy_text), LANG_SCNG(yy_leng), line);
			}
			break;
		case ON_FEEDBACK:
			tokens_ht = Z_ARRVAL_P(token_stream);
			token_zv = zend_hash_index_find(tokens_ht, zend_hash_num_elements(tokens_ht) - 1);
			if (token_zv && Z_TYPE_P(token_zv) == IS_ARRAY) {
				ZVAL_LONG(zend_hash_index_find(Z_ARRVAL_P(token_zv), 0), token);
			}
			break;
		case ON_STOP:
			if (LANG_SCNG(yy_cursor) != LANG_SCNG(yy_limit)) {
				add_token(token_stream, T_INLINE_HTML, LANG_SCNG(yy_cursor),
					LANG_SCNG(yy_limit) - LANG_SCNG(yy_cursor), CG(zend_lineno));
			}
			break;
	}
}