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
struct effect_parser {int /*<<< orphan*/  cfp; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEX_ERROR ; 
 int /*<<< orphan*/  cf_adderror (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void report_invalid_func_keyword(struct effect_parser *ep,
					       const char *name, bool val)
{
	if (val)
		cf_adderror(&ep->cfp,
			    "'$1' keyword cannot be used with a "
			    "function",
			    LEX_ERROR, name, NULL, NULL);
}