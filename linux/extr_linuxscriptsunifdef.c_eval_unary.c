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
struct ops {int dummy; } ;
typedef  scalar_t__ Linetype ;

/* Variables and functions */
 scalar_t__ LT_ERROR ; 
 scalar_t__ LT_FALSE ; 
 scalar_t__ LT_IF ; 
 scalar_t__ LT_TRUE ; 
 int constexpr ; 
 int /*<<< orphan*/  debug (char*,struct ops const*,...) ; 
 scalar_t__ endsym (char const) ; 
 int eval_ops ; 
 scalar_t__ eval_table (int,int*,char const**) ; 
 int findsym (char const*) ; 
 scalar_t__ isdigit (unsigned char) ; 
 char* skipargs (char const*) ; 
 char* skipcomment (char const*) ; 
 char* skipsym (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 
 char** value ; 

__attribute__((used)) static Linetype
eval_unary(const struct ops *ops, int *valp, const char **cpp)
{
	const char *cp;
	char *ep;
	int sym;
	bool defparen;
	Linetype lt;

	cp = skipcomment(*cpp);
	if (*cp == '!') {
		debug("eval%d !", ops - eval_ops);
		cp++;
		lt = eval_unary(ops, valp, &cp);
		if (lt == LT_ERROR)
			return (LT_ERROR);
		if (lt != LT_IF) {
			*valp = !*valp;
			lt = *valp ? LT_TRUE : LT_FALSE;
		}
	} else if (*cp == '(') {
		cp++;
		debug("eval%d (", ops - eval_ops);
		lt = eval_table(eval_ops, valp, &cp);
		if (lt == LT_ERROR)
			return (LT_ERROR);
		cp = skipcomment(cp);
		if (*cp++ != ')')
			return (LT_ERROR);
	} else if (isdigit((unsigned char)*cp)) {
		debug("eval%d number", ops - eval_ops);
		*valp = strtol(cp, &ep, 0);
		if (ep == cp)
			return (LT_ERROR);
		lt = *valp ? LT_TRUE : LT_FALSE;
		cp = skipsym(cp);
	} else if (strncmp(cp, "defined", 7) == 0 && endsym(cp[7])) {
		cp = skipcomment(cp+7);
		debug("eval%d defined", ops - eval_ops);
		if (*cp == '(') {
			cp = skipcomment(cp+1);
			defparen = true;
		} else {
			defparen = false;
		}
		sym = findsym(cp);
		if (sym < 0) {
			lt = LT_IF;
		} else {
			*valp = (value[sym] != NULL);
			lt = *valp ? LT_TRUE : LT_FALSE;
		}
		cp = skipsym(cp);
		cp = skipcomment(cp);
		if (defparen && *cp++ != ')')
			return (LT_ERROR);
		constexpr = false;
	} else if (!endsym(*cp)) {
		debug("eval%d symbol", ops - eval_ops);
		sym = findsym(cp);
		cp = skipsym(cp);
		if (sym < 0) {
			lt = LT_IF;
			cp = skipargs(cp);
		} else if (value[sym] == NULL) {
			*valp = 0;
			lt = LT_FALSE;
		} else {
			*valp = strtol(value[sym], &ep, 0);
			if (*ep != '\0' || ep == value[sym])
				return (LT_ERROR);
			lt = *valp ? LT_TRUE : LT_FALSE;
			cp = skipargs(cp);
		}
		constexpr = false;
	} else {
		debug("eval%d bad expr", ops - eval_ops);
		return (LT_ERROR);
	}

	*cpp = cp;
	debug("eval%d = %d", ops - eval_ops, *valp);
	return (lt);
}