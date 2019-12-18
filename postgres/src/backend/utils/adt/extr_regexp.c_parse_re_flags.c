#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_3__ {int cflags; int glob; } ;
typedef  TYPE_1__ pg_re_flags ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int REG_ADVANCED ; 
 int REG_EXPANDED ; 
 int REG_EXTENDED ; 
 int REG_ICASE ; 
 int REG_NEWLINE ; 
 int REG_NLANCH ; 
 int REG_NLSTOP ; 
 int REG_QUOTE ; 
 char* VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char) ; 

__attribute__((used)) static void
parse_re_flags(pg_re_flags *flags, text *opts)
{
	/* regex flavor is always folded into the compile flags */
	flags->cflags = REG_ADVANCED;
	flags->glob = false;

	if (opts)
	{
		char	   *opt_p = VARDATA_ANY(opts);
		int			opt_len = VARSIZE_ANY_EXHDR(opts);
		int			i;

		for (i = 0; i < opt_len; i++)
		{
			switch (opt_p[i])
			{
				case 'g':
					flags->glob = true;
					break;
				case 'b':		/* BREs (but why???) */
					flags->cflags &= ~(REG_ADVANCED | REG_EXTENDED | REG_QUOTE);
					break;
				case 'c':		/* case sensitive */
					flags->cflags &= ~REG_ICASE;
					break;
				case 'e':		/* plain EREs */
					flags->cflags |= REG_EXTENDED;
					flags->cflags &= ~(REG_ADVANCED | REG_QUOTE);
					break;
				case 'i':		/* case insensitive */
					flags->cflags |= REG_ICASE;
					break;
				case 'm':		/* Perloid synonym for n */
				case 'n':		/* \n affects ^ $ . [^ */
					flags->cflags |= REG_NEWLINE;
					break;
				case 'p':		/* ~Perl, \n affects . [^ */
					flags->cflags |= REG_NLSTOP;
					flags->cflags &= ~REG_NLANCH;
					break;
				case 'q':		/* literal string */
					flags->cflags |= REG_QUOTE;
					flags->cflags &= ~(REG_ADVANCED | REG_EXTENDED);
					break;
				case 's':		/* single line, \n ordinary */
					flags->cflags &= ~REG_NEWLINE;
					break;
				case 't':		/* tight syntax */
					flags->cflags &= ~REG_EXPANDED;
					break;
				case 'w':		/* weird, \n affects ^ $ only */
					flags->cflags &= ~REG_NLSTOP;
					flags->cflags |= REG_NLANCH;
					break;
				case 'x':		/* expanded syntax */
					flags->cflags |= REG_EXPANDED;
					break;
				default:
					ereport(ERROR,
							(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
							 errmsg("invalid regular expression option: \"%c\"",
									opt_p[i])));
					break;
			}
		}
	}
}