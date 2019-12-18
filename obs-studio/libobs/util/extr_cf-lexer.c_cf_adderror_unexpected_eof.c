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
 int /*<<< orphan*/  cf_adderror (struct cf_preprocessor*,struct cf_token const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cf_adderror_unexpected_eof(struct cf_preprocessor *pp,
					      const struct cf_token *token)
{
	cf_adderror(pp, token, "Unexpected end of file", NULL, NULL, NULL);
}