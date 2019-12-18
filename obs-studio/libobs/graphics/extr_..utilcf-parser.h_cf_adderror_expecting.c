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
 int /*<<< orphan*/  LEX_ERROR ; 
 int /*<<< orphan*/  cf_adderror (struct cf_parser*,char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void cf_adderror_expecting(struct cf_parser *p,
					 const char *expected)
{
	cf_adderror(p, "Expected '$1'", LEX_ERROR, expected, NULL, NULL);
}