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
struct cf_token {int dummy; } ;
struct cf_preprocessor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEX_ERROR ; 
 int /*<<< orphan*/  cf_addew (struct cf_preprocessor*,struct cf_token const*,char const*,int /*<<< orphan*/ ,char const*,char const*,char const*) ; 

__attribute__((used)) static inline void cf_adderror(struct cf_preprocessor *pp,
			       const struct cf_token *token, const char *error,
			       const char *val1, const char *val2,
			       const char *val3)
{
	cf_addew(pp, token, error, LEX_ERROR, val1, val2, val3);
}