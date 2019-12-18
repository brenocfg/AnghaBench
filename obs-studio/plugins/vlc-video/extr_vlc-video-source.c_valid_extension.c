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
struct dstr {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 char* EXTENSIONS_MEDIA ; 
 scalar_t__ dstr_cmp (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_copy (struct dstr*,char const*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_ncopy (struct dstr*,char const*,int) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static bool valid_extension(const char *ext)
{
	struct dstr test = {0};
	bool valid = false;
	const char *b;
	const char *e;

	if (!ext || !*ext)
		return false;

	b = EXTENSIONS_MEDIA + 1;
	e = strchr(b, ';');

	for (;;) {
		if (e)
			dstr_ncopy(&test, b, e - b);
		else
			dstr_copy(&test, b);

		if (dstr_cmp(&test, ext) == 0) {
			valid = true;
			break;
		}

		if (!e)
			break;

		b = e + 2;
		e = strchr(b, ';');
	}

	dstr_free(&test);
	return valid;
}