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
struct match_token {int token; char const* pattern; } ;

/* Variables and functions */
 int Opt_err ; 
 int /*<<< orphan*/  strchr (char const*,char) ; 
 struct match_token* tokens ; 

__attribute__((used)) static const char *token2str(int token)
{
	const struct match_token *t;

	for (t = tokens; t->token != Opt_err; t++)
		if (t->token == token && !strchr(t->pattern, '='))
			break;
	return t->pattern;
}