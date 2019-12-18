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
 scalar_t__ DBCS_KOR ; 
 int F_BLANK ; 
 int NUL ; 
 scalar_t__ cls_bigword ; 
 int dbcs_class (unsigned int,int) ; 
 scalar_t__ enc_dbcs ; 
 scalar_t__ enc_utf8 ; 
 int gchar_cursor () ; 
 scalar_t__ p_altkeymap ; 
 int utf_class (int) ; 
 scalar_t__ vim_iswordc (int) ; 

__attribute__((used)) static int
cls()
{
    int	    c;

    c = gchar_cursor();
#ifdef FEAT_FKMAP	/* when 'akm' (Farsi mode), take care of Farsi blank */
    if (p_altkeymap && c == F_BLANK)
	return 0;
#endif
    if (c == ' ' || c == '\t' || c == NUL)
	return 0;
#ifdef FEAT_MBYTE
    if (enc_dbcs != 0 && c > 0xFF)
    {
	/* If cls_bigword, report multi-byte chars as class 1. */
	if (enc_dbcs == DBCS_KOR && cls_bigword)
	    return 1;

	/* process code leading/trailing bytes */
	return dbcs_class(((unsigned)c >> 8), (c & 0xFF));
    }
    if (enc_utf8)
    {
	c = utf_class(c);
	if (c != 0 && cls_bigword)
	    return 1;
	return c;
    }
#endif

    /* If cls_bigword is TRUE, report all non-blanks as class 1. */
    if (cls_bigword)
	return 1;

    if (vim_iswordc(c))
	return 2;
    return 1;
}