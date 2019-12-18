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
 int /*<<< orphan*/  cf_next_token (struct cf_parser*) ; 

__attribute__((used)) static inline bool cf_next_valid_token(struct cf_parser *p)
{
	if (!cf_next_token(p)) {
		cf_adderror_unexpected_eof(p);
		return false;
	}

	return true;
}