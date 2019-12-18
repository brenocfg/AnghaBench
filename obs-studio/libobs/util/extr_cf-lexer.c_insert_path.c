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
struct dstr {int /*<<< orphan*/  member_0; } ;
struct cf_preprocessor {TYPE_1__* lex; } ;
struct TYPE_2__ {char* file; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_insert_dstr (struct dstr*,int /*<<< orphan*/ ,struct dstr*) ; 
 int /*<<< orphan*/  dstr_ncopy (struct dstr*,char const*,int) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static inline void insert_path(struct cf_preprocessor *pp,
			       struct dstr *str_file)
{
	const char *file;
	const char *slash;

	if (pp && pp->lex && pp->lex->file) {
		file = pp->lex->file;
		slash = strrchr(file, '/');
		if (slash) {
			struct dstr path = {0};
			dstr_ncopy(&path, file, slash - file + 1);
			dstr_insert_dstr(str_file, 0, &path);
			dstr_free(&path);
		}
	}
}