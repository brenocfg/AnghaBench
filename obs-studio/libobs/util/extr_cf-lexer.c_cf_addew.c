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
typedef  int /*<<< orphan*/  uint32_t ;
struct dstr {char const* array; } ;
struct cf_token {TYPE_1__* lex; } ;
struct cf_preprocessor {int /*<<< orphan*/  ed; } ;
struct TYPE_2__ {int /*<<< orphan*/  file; } ;

/* Variables and functions */
 int /*<<< orphan*/  cf_gettokenoffset (struct cf_preprocessor*,struct cf_token const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init (struct dstr*) ; 
 int /*<<< orphan*/  dstr_safe_printf (struct dstr*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error_data_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void cf_addew(struct cf_preprocessor *pp, const struct cf_token *token,
		     const char *message, int error_level, const char *val1,
		     const char *val2, const char *val3)
{
	uint32_t row, col;
	cf_gettokenoffset(pp, token, &row, &col);

	if (!val1 && !val2 && !val3) {
		error_data_add(pp->ed, token->lex->file, row, col, message,
			       error_level);
	} else {
		struct dstr formatted;
		dstr_init(&formatted);
		dstr_safe_printf(&formatted, message, val1, val2, val3, NULL);

		error_data_add(pp->ed, token->lex->file, row, col,
			       formatted.array, error_level);
		dstr_free(&formatted);
	}
}