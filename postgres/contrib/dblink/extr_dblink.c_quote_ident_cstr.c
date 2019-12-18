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
typedef  int /*<<< orphan*/  text ;

/* Variables and functions */
 int /*<<< orphan*/ * DatumGetTextPP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cstring_to_text (char*) ; 
 int /*<<< orphan*/  quote_ident ; 
 char* text_to_cstring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *
quote_ident_cstr(char *rawstr)
{
	text	   *rawstr_text;
	text	   *result_text;
	char	   *result;

	rawstr_text = cstring_to_text(rawstr);
	result_text = DatumGetTextPP(DirectFunctionCall1(quote_ident,
													 PointerGetDatum(rawstr_text)));
	result = text_to_cstring(result_text);

	return result;
}