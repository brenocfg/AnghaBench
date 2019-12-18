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
struct cf_parser {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cf_adderror_unexpected_eof (struct cf_parser*) ; 
 int /*<<< orphan*/  cf_go_to_token (struct cf_parser*,char const*,char const*) ; 

__attribute__((used)) static inline bool cf_go_to_valid_token(struct cf_parser *p, const char *str1,
					const char *str2)
{
	if (!cf_go_to_token(p, str1, str2)) {
		cf_adderror_unexpected_eof(p);
		return false;
	}

	return true;
}