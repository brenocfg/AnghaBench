#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char opt_char; int need_param; int /*<<< orphan*/ * opt_name; } ;
typedef  TYPE_1__ opt_struct ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* safe_emalloc (int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int parse_opts(char * opts, opt_struct ** result)
{
	opt_struct * paras = NULL;
	unsigned int i, count = 0;
	unsigned int opts_len = (unsigned int)strlen(opts);

	for (i = 0; i < opts_len; i++) {
		if ((opts[i] >= 48 && opts[i] <= 57) ||
			(opts[i] >= 65 && opts[i] <= 90) ||
			(opts[i] >= 97 && opts[i] <= 122)
		) {
			count++;
		}
	}

	paras = safe_emalloc(sizeof(opt_struct), count, 0);
	memset(paras, 0, sizeof(opt_struct) * count);
	*result = paras;
	while ( (*opts >= 48 && *opts <= 57) || /* 0 - 9 */
			(*opts >= 65 && *opts <= 90) || /* A - Z */
			(*opts >= 97 && *opts <= 122)   /* a - z */
	) {
		paras->opt_char = *opts;
		paras->need_param = *(++opts) == ':';
		paras->opt_name = NULL;
		if (paras->need_param == 1) {
			opts++;
			if (*opts == ':') {
				paras->need_param++;
				opts++;
			}
		}
		paras++;
	}
	return count;
}