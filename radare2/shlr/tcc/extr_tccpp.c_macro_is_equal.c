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
typedef  int /*<<< orphan*/  CValue ;

/* Variables and functions */
 int /*<<< orphan*/  STRING_MAX_SIZE ; 
 int /*<<< orphan*/  TOK_GET (int*,int const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_tok_str (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pstrcpy (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int macro_is_equal(const int *a, const int *b)
{
	char buf[STRING_MAX_SIZE + 1];
	CValue cv;
	int t;
	while (*a && *b) {
		TOK_GET (&t, &a, &cv);
		pstrcpy (buf, sizeof buf, get_tok_str (t, &cv));
		TOK_GET (&t, &b, &cv);
		if (strcmp (buf, get_tok_str (t, &cv))) {
			return 0;
		}
	}
	return !(*a || *b);
}