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
typedef  scalar_t__ char_u ;

/* Variables and functions */
 int /*<<< orphan*/  LC_COLLATE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 scalar_t__ NUL ; 
 scalar_t__ get_locale_val (int /*<<< orphan*/ ) ; 
 scalar_t__* gettext_lang (scalar_t__*) ; 
 scalar_t__* mch_getenv (scalar_t__*) ; 

char_u *
get_mess_lang()
{
    char_u *p;

# ifdef HAVE_GET_LOCALE_VAL
#  if defined(LC_MESSAGES)
    p = (char_u *)get_locale_val(LC_MESSAGES);
#  else
    /* This is necessary for Win32, where LC_MESSAGES is not defined and $LANG
     * may be set to the LCID number.  LC_COLLATE is the best guess, LC_TIME
     * and LC_MONETARY may be set differently for a Japanese working in the
     * US. */
    p = (char_u *)get_locale_val(LC_COLLATE);
#  endif
# else
    p = mch_getenv((char_u *)"LC_ALL");
    if (p == NULL || *p == NUL)
    {
	p = mch_getenv((char_u *)"LC_MESSAGES");
	if (p == NULL || *p == NUL)
	    p = mch_getenv((char_u *)"LANG");
    }
# endif
# ifdef WIN32
    p = gettext_lang(p);
# endif
    return p;
}