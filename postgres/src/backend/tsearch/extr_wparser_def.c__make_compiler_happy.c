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
 int /*<<< orphan*/  p_isEOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isalnum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isalpha (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isdigit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_iseqC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_islower (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isneC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isnotalnum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isnotalpha (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isnotdigit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isnotlower (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isnotprint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isnotpunct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isnotspace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isnotupper (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isnotxdigit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isprint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_ispunct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isspace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isupper (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_isxdigit (int /*<<< orphan*/ *) ; 

void
_make_compiler_happy(void)
{
	p_isalnum(NULL);
	p_isnotalnum(NULL);
	p_isalpha(NULL);
	p_isnotalpha(NULL);
	p_isdigit(NULL);
	p_isnotdigit(NULL);
	p_islower(NULL);
	p_isnotlower(NULL);
	p_isprint(NULL);
	p_isnotprint(NULL);
	p_ispunct(NULL);
	p_isnotpunct(NULL);
	p_isspace(NULL);
	p_isnotspace(NULL);
	p_isupper(NULL);
	p_isnotupper(NULL);
	p_isxdigit(NULL);
	p_isnotxdigit(NULL);
	p_isEOF(NULL);
	p_iseqC(NULL);
	p_isneC(NULL);
}