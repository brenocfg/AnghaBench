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
struct vars {int dummy; } ;
struct cname {int /*<<< orphan*/  code; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  const chr ;

/* Variables and functions */
 int /*<<< orphan*/  const CHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NOTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_ECOLLATE ; 
 int /*<<< orphan*/  REG_ULOCALE ; 
 int /*<<< orphan*/  assert (int) ; 
 struct cname* cnames ; 
 scalar_t__ pg_char_and_wchar_strncmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 size_t strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static chr
element(struct vars *v,			/* context */
		const chr *startp,		/* points to start of name */
		const chr *endp)		/* points just past end of name */
{
	const struct cname *cn;
	size_t		len;

	/* generic:  one-chr names stand for themselves */
	assert(startp < endp);
	len = endp - startp;
	if (len == 1)
		return *startp;

	NOTE(REG_ULOCALE);

	/* search table */
	for (cn = cnames; cn->name != NULL; cn++)
	{
		if (strlen(cn->name) == len &&
			pg_char_and_wchar_strncmp(cn->name, startp, len) == 0)
		{
			break;				/* NOTE BREAK OUT */
		}
	}
	if (cn->name != NULL)
		return CHR(cn->code);

	/* couldn't find it */
	ERR(REG_ECOLLATE);
	return 0;
}