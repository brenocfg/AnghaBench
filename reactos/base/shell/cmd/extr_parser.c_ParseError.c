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

/* Variables and functions */
 int /*<<< orphan*/ * CurrentToken ; 
 scalar_t__ CurrentTokenType ; 
 scalar_t__ TOK_END ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bParseError ; 
 int /*<<< orphan*/  error_syntax (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ParseError(void)
{
    error_syntax(CurrentTokenType != TOK_END ? CurrentToken : NULL);
    bParseError = TRUE;
}