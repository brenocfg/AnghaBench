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
struct cf_parser {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cf_adderror_unexpected_eof (struct cf_parser*) ; 
 int cf_peek_token (struct cf_parser*,struct cf_token*) ; 

__attribute__((used)) static inline bool cf_peek_valid_token(struct cf_parser *p,
				       struct cf_token *peek)
{
	bool success = cf_peek_token(p, peek);
	if (!success)
		cf_adderror_unexpected_eof(p);
	return success;
}