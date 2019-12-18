#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dstr {int /*<<< orphan*/  array; scalar_t__ len; } ;
struct TYPE_3__ {int /*<<< orphan*/  array; } ;
struct cf_token {TYPE_1__ str; } ;
struct TYPE_4__ {size_t num; struct cf_lexer* array; } ;
struct cf_preprocessor {TYPE_2__ dependencies; } ;
struct cf_lexer {int /*<<< orphan*/  file; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (char*) ; 
 int /*<<< orphan*/  cf_adderror (struct cf_preprocessor*,struct cf_token const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct cf_token* cf_lexer_get_tokens (struct cf_lexer*) ; 
 int /*<<< orphan*/  cf_lexer_init (struct cf_lexer*) ; 
 int /*<<< orphan*/  cf_lexer_lex (struct cf_lexer*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cf_preprocess_tokens (struct cf_preprocessor*,int,struct cf_token**) ; 
 int /*<<< orphan*/  da_push_back (TYPE_2__,struct cf_lexer*) ; 
 int /*<<< orphan*/  dstr_copy_strref (struct dstr*,TYPE_1__*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_init (struct dstr*) ; 
 int /*<<< orphan*/  dstr_mid (struct dstr*,struct dstr*,int,scalar_t__) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_path (struct cf_preprocessor*,struct dstr*) ; 
 int /*<<< orphan*/ * os_fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  os_fread_utf8 (int /*<<< orphan*/ *,char**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cf_include_file(struct cf_preprocessor *pp,
			    const struct cf_token *file_token)
{
	struct cf_lexer new_lex;
	struct dstr str_file;
	FILE *file;
	char *file_data;
	struct cf_token *tokens;
	size_t i;

	dstr_init(&str_file);
	dstr_copy_strref(&str_file, &file_token->str);
	dstr_mid(&str_file, &str_file, 1, str_file.len - 2);
	insert_path(pp, &str_file);

	/* if dependency already exists, run preprocessor on it */
	for (i = 0; i < pp->dependencies.num; i++) {
		struct cf_lexer *dep = pp->dependencies.array + i;

		if (strcmp(dep->file, str_file.array) == 0) {
			tokens = cf_lexer_get_tokens(dep);
			cf_preprocess_tokens(pp, false, &tokens);
			goto exit;
		}
	}

	file = os_fopen(str_file.array, "rb");
	if (!file) {
		cf_adderror(pp, file_token, "Could not open file '$1'",
			    file_token->str.array, NULL, NULL);
		goto exit;
	}

	os_fread_utf8(file, &file_data);
	fclose(file);

	cf_lexer_init(&new_lex);
	cf_lexer_lex(&new_lex, file_data, str_file.array);
	tokens = cf_lexer_get_tokens(&new_lex);
	cf_preprocess_tokens(pp, false, &tokens);
	bfree(file_data);

	da_push_back(pp->dependencies, &new_lex);

exit:
	dstr_free(&str_file);
}