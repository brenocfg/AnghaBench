#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lconv {char* negative_sign; char* positive_sign; char* decimal_point; char* thousands_sep; char* currency_symbol; } ;
struct TYPE_5__ {scalar_t__ need_locale; } ;
struct TYPE_4__ {char* L_negative_sign; char* L_positive_sign; char* decimal; char* L_thousands_sep; char* L_currency_symbol; TYPE_3__* Num; } ;
typedef  TYPE_1__ NUMProc ;

/* Variables and functions */
 int /*<<< orphan*/  IS_LDECIMAL (TYPE_3__*) ; 
 struct lconv* PGLC_localeconv () ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
NUM_prepare_locale(NUMProc *Np)
{
	if (Np->Num->need_locale)
	{
		struct lconv *lconv;

		/*
		 * Get locales
		 */
		lconv = PGLC_localeconv();

		/*
		 * Positive / Negative number sign
		 */
		if (lconv->negative_sign && *lconv->negative_sign)
			Np->L_negative_sign = lconv->negative_sign;
		else
			Np->L_negative_sign = "-";

		if (lconv->positive_sign && *lconv->positive_sign)
			Np->L_positive_sign = lconv->positive_sign;
		else
			Np->L_positive_sign = "+";

		/*
		 * Number decimal point
		 */
		if (lconv->decimal_point && *lconv->decimal_point)
			Np->decimal = lconv->decimal_point;

		else
			Np->decimal = ".";

		if (!IS_LDECIMAL(Np->Num))
			Np->decimal = ".";

		/*
		 * Number thousands separator
		 *
		 * Some locales (e.g. broken glibc pt_BR), have a comma for decimal,
		 * but "" for thousands_sep, so we set the thousands_sep too.
		 * http://archives.postgresql.org/pgsql-hackers/2007-11/msg00772.php
		 */
		if (lconv->thousands_sep && *lconv->thousands_sep)
			Np->L_thousands_sep = lconv->thousands_sep;
		/* Make sure thousands separator doesn't match decimal point symbol. */
		else if (strcmp(Np->decimal, ",") !=0)
			Np->L_thousands_sep = ",";
		else
			Np->L_thousands_sep = ".";

		/*
		 * Currency symbol
		 */
		if (lconv->currency_symbol && *lconv->currency_symbol)
			Np->L_currency_symbol = lconv->currency_symbol;
		else
			Np->L_currency_symbol = " ";
	}
	else
	{
		/*
		 * Default values
		 */
		Np->L_negative_sign = "-";
		Np->L_positive_sign = "+";
		Np->decimal = ".";

		Np->L_thousands_sep = ",";
		Np->L_currency_symbol = " ";
	}
}