#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct dstr {char const* array; } ;
struct cf_parser {TYPE_3__* cur_token; int /*<<< orphan*/  error_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  array; } ;
struct TYPE_6__ {TYPE_2__* lex; TYPE_1__ unmerged_str; } ;
struct TYPE_5__ {int /*<<< orphan*/  file; int /*<<< orphan*/  base_lexer; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init (struct dstr*) ; 
 int /*<<< orphan*/  dstr_safe_printf (struct dstr*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error_data_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  lexer_getstroffset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void cf_adderror(struct cf_parser *p, const char *error, int level,
		 const char *val1, const char *val2, const char *val3)
{
	uint32_t row, col;
	lexer_getstroffset(&p->cur_token->lex->base_lexer,
			   p->cur_token->unmerged_str.array, &row, &col);

	if (!val1 && !val2 && !val3) {
		error_data_add(&p->error_list, p->cur_token->lex->file, row,
			       col, error, level);
	} else {
		struct dstr formatted;
		dstr_init(&formatted);
		dstr_safe_printf(&formatted, error, val1, val2, val3, NULL);

		error_data_add(&p->error_list, p->cur_token->lex->file, row,
			       col, formatted.array, level);

		dstr_free(&formatted);
	}
}