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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int php_code_type ;

/* Variables and functions */
 int /*<<< orphan*/  CG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZEND_ASSERT (char*) ; 
 int body ; 
 int /*<<< orphan*/ * cli_get_prompt (char*,char) ; 
#define  comment_block 136 
#define  comment_line 135 
#define  dstring 134 
#define  dstring_esc 133 
#define  heredoc 132 
#define  heredoc_start 131 
#define  outside 130 
 int /*<<< orphan*/  short_tags ; 
#define  sstring 129 
#define  sstring_esc 128 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int cli_is_valid_code(char *code, size_t len, zend_string **prompt) /* {{{ */
{
	int valid_end = 1, last_valid_end;
	int brackets_count = 0;
	int brace_count = 0;
	size_t i;
	php_code_type code_type = body;
	char *heredoc_tag = NULL;
	size_t heredoc_len;

	for (i = 0; i < len; ++i) {
		switch(code_type) {
			default:
				switch(code[i]) {
					case '{':
						brackets_count++;
						valid_end = 0;
						break;
					case '}':
						if (brackets_count > 0) {
							brackets_count--;
						}
						valid_end = brackets_count ? 0 : 1;
						break;
					case '(':
						brace_count++;
						valid_end = 0;
						break;
					case ')':
						if (brace_count > 0) {
							brace_count--;
						}
						valid_end = 0;
						break;
					case ';':
						valid_end = brace_count == 0 && brackets_count == 0;
						break;
					case ' ':
					case '\r':
					case '\n':
					case '\t':
						break;
					case '\'':
						code_type = sstring;
						break;
					case '"':
						code_type = dstring;
						break;
					case '#':
						code_type = comment_line;
						break;
					case '/':
						if (code[i+1] == '/') {
							i++;
							code_type = comment_line;
							break;
						}
						if (code[i+1] == '*') {
							last_valid_end = valid_end;
							valid_end = 0;
							code_type = comment_block;
							i++;
							break;
						}
						valid_end = 0;
						break;
					case '?':
						if (code[i+1] == '>') {
							i++;
							code_type = outside;
							break;
						}
						valid_end = 0;
						break;
					case '<':
						valid_end = 0;
						if (i + 2 < len && code[i+1] == '<' && code[i+2] == '<') {
							i += 2;
							code_type = heredoc_start;
							heredoc_tag = NULL;
							heredoc_len = 0;
						}
						break;
					default:
						valid_end = 0;
						break;
				}
				break;
			case sstring:
				if (code[i] == '\\') {
					code_type = sstring_esc;
				} else {
					if (code[i] == '\'') {
						code_type = body;
					}
				}
				break;
			case sstring_esc:
				code_type = sstring;
				break;
			case dstring:
				if (code[i] == '\\') {
					code_type = dstring_esc;
				} else {
					if (code[i] == '"') {
						code_type = body;
					}
				}
				break;
			case dstring_esc:
				code_type = dstring;
				break;
			case comment_line:
				if (code[i] == '\n') {
					code_type = body;
				}
				break;
			case comment_block:
				if (code[i-1] == '*' && code[i] == '/') {
					code_type = body;
					valid_end = last_valid_end;
				}
				break;
			case heredoc_start:
				switch(code[i]) {
					case ' ':
					case '\t':
					case '\'':
						break;
					case '\r':
					case '\n':
						if (heredoc_tag) {
							code_type = heredoc;
						} else {
							/* Malformed heredoc without label */
							code_type = body;
						}
						break;
					default:
						if (!heredoc_tag) {
							heredoc_tag = code+i;
						}
						heredoc_len++;
						break;
				}
				break;
			case heredoc:
				ZEND_ASSERT(heredoc_tag);
				if (!strncmp(code + i - heredoc_len + 1, heredoc_tag, heredoc_len)) {
					unsigned char c = code[i + 1];
					char *p = code + i - heredoc_len;

					if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_' || c >= 0x80) break;
					while (*p == ' ' || *p == '\t') p--;
					if (*p != '\n') break;
					code_type = body;
				}
				break;
			case outside:
				if ((CG(short_tags) && !strncmp(code+i-1, "<?", 2))
				||  (i > 3 && !strncmp(code+i-4, "<?php", 5))
				) {
					code_type = body;
				}
				break;
		}
	}

	switch (code_type) {
		default:
			if (brace_count) {
				*prompt = cli_get_prompt("php", '(');
			} else if (brackets_count) {
				*prompt = cli_get_prompt("php", '{');
			} else {
				*prompt = cli_get_prompt("php", '>');
			}
			break;
		case sstring:
		case sstring_esc:
			*prompt = cli_get_prompt("php", '\'');
			break;
		case dstring:
		case dstring_esc:
			*prompt = cli_get_prompt("php", '"');
			break;
		case comment_block:
			*prompt = cli_get_prompt("/* ", '>');
			break;
		case heredoc:
			*prompt = cli_get_prompt("<<<", '>');
			break;
		case outside:
			*prompt = cli_get_prompt("   ", '>');
			break;
	}

	if (!valid_end || brackets_count) {
		return 0;
	} else {
		return 1;
	}
}