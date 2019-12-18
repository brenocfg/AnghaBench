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
struct cvec {int dummy; } ;
typedef  enum classes { ____Placeholder_classes } classes ;
typedef  int /*<<< orphan*/  chr ;

/* Variables and functions */
#define  CC_ALNUM 140 
#define  CC_ALPHA 139 
#define  CC_ASCII 138 
#define  CC_BLANK 137 
#define  CC_CNTRL 136 
#define  CC_DIGIT 135 
#define  CC_GRAPH 134 
#define  CC_LOWER 133 
#define  CC_PRINT 132 
#define  CC_PUNCT 131 
#define  CC_SPACE 130 
#define  CC_UPPER 129 
#define  CC_XDIGIT 128 
 int /*<<< orphan*/  ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_ECTYPE ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  addchr (struct cvec*,char) ; 
 int /*<<< orphan*/  addrange (struct cvec*,char,float) ; 
 char** classNames ; 
 struct cvec* getcvec (struct vars*,int,int) ; 
 scalar_t__ pg_char_and_wchar_strncmp (char const* const,int /*<<< orphan*/  const*,size_t) ; 
 struct cvec* pg_ctype_get_cache (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pg_wc_isalnum ; 
 int /*<<< orphan*/  pg_wc_isalpha ; 
 int /*<<< orphan*/  pg_wc_isdigit ; 
 int /*<<< orphan*/  pg_wc_isgraph ; 
 int /*<<< orphan*/  pg_wc_islower ; 
 int /*<<< orphan*/  pg_wc_isprint ; 
 int /*<<< orphan*/  pg_wc_ispunct ; 
 int /*<<< orphan*/  pg_wc_isspace ; 
 int /*<<< orphan*/  pg_wc_isupper ; 
 size_t strlen (char const* const) ; 

__attribute__((used)) static struct cvec *
cclass(struct vars *v,			/* context */
	   const chr *startp,		/* where the name starts */
	   const chr *endp,			/* just past the end of the name */
	   int cases)				/* case-independent? */
{
	size_t		len;
	struct cvec *cv = NULL;
	const char *const *namePtr;
	int			i,
				index;

	/*
	 * Map the name to the corresponding enumerated value.
	 */
	len = endp - startp;
	index = -1;
	for (namePtr = classNames, i = 0; *namePtr != NULL; namePtr++, i++)
	{
		if (strlen(*namePtr) == len &&
			pg_char_and_wchar_strncmp(*namePtr, startp, len) == 0)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		ERR(REG_ECTYPE);
		return NULL;
	}

	/*
	 * Remap lower and upper to alpha if the match is case insensitive.
	 */

	if (cases &&
		((enum classes) index == CC_LOWER ||
		 (enum classes) index == CC_UPPER))
		index = (int) CC_ALPHA;

	/*
	 * Now compute the character class contents.  For classes that are based
	 * on the behavior of a <wctype.h> or <ctype.h> function, we use
	 * pg_ctype_get_cache so that we can cache the results.  Other classes
	 * have definitions that are hard-wired here, and for those we just
	 * construct a transient cvec on the fly.
	 *
	 * NB: keep this code in sync with cclass_column_index(), below.
	 */

	switch ((enum classes) index)
	{
		case CC_PRINT:
			cv = pg_ctype_get_cache(pg_wc_isprint, index);
			break;
		case CC_ALNUM:
			cv = pg_ctype_get_cache(pg_wc_isalnum, index);
			break;
		case CC_ALPHA:
			cv = pg_ctype_get_cache(pg_wc_isalpha, index);
			break;
		case CC_ASCII:
			/* hard-wired meaning */
			cv = getcvec(v, 0, 1);
			if (cv)
				addrange(cv, 0, 0x7f);
			break;
		case CC_BLANK:
			/* hard-wired meaning */
			cv = getcvec(v, 2, 0);
			addchr(cv, '\t');
			addchr(cv, ' ');
			break;
		case CC_CNTRL:
			/* hard-wired meaning */
			cv = getcvec(v, 0, 2);
			addrange(cv, 0x0, 0x1f);
			addrange(cv, 0x7f, 0x9f);
			break;
		case CC_DIGIT:
			cv = pg_ctype_get_cache(pg_wc_isdigit, index);
			break;
		case CC_PUNCT:
			cv = pg_ctype_get_cache(pg_wc_ispunct, index);
			break;
		case CC_XDIGIT:

			/*
			 * It's not clear how to define this in non-western locales, and
			 * even less clear that there's any particular use in trying. So
			 * just hard-wire the meaning.
			 */
			cv = getcvec(v, 0, 3);
			if (cv)
			{
				addrange(cv, '0', '9');
				addrange(cv, 'a', 'f');
				addrange(cv, 'A', 'F');
			}
			break;
		case CC_SPACE:
			cv = pg_ctype_get_cache(pg_wc_isspace, index);
			break;
		case CC_LOWER:
			cv = pg_ctype_get_cache(pg_wc_islower, index);
			break;
		case CC_UPPER:
			cv = pg_ctype_get_cache(pg_wc_isupper, index);
			break;
		case CC_GRAPH:
			cv = pg_ctype_get_cache(pg_wc_isgraph, index);
			break;
	}

	/* If cv is NULL now, the reason must be "out of memory" */
	if (cv == NULL)
		ERR(REG_ESPACE);
	return cv;
}