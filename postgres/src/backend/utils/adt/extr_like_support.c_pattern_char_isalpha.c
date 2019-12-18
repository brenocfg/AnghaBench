#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* pg_locale_t ;
struct TYPE_4__ {int /*<<< orphan*/  lt; } ;
struct TYPE_5__ {scalar_t__ provider; TYPE_1__ info; } ;

/* Variables and functions */
 scalar_t__ COLLPROVIDER_ICU ; 
 scalar_t__ COLLPROVIDER_LIBC ; 
 scalar_t__ IS_HIGHBIT_SET (char) ; 
 int isalpha (unsigned char) ; 
 int isalpha_l (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pattern_char_isalpha(char c, bool is_multibyte,
					 pg_locale_t locale, bool locale_is_c)
{
	if (locale_is_c)
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	else if (is_multibyte && IS_HIGHBIT_SET(c))
		return true;
	else if (locale && locale->provider == COLLPROVIDER_ICU)
		return IS_HIGHBIT_SET(c) ||
			(c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
#ifdef HAVE_LOCALE_T
	else if (locale && locale->provider == COLLPROVIDER_LIBC)
		return isalpha_l((unsigned char) c, locale->info.lt);
#endif
	else
		return isalpha((unsigned char) c);
}