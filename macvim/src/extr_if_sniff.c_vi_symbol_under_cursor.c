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
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int /*<<< orphan*/  FIND_IDENT ; 
 int find_ident_under_cursor (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
vi_symbol_under_cursor()
{
    int		len;
    char	*symbolp;
    char	*p;
    static char sniff_symbol[256];

    len = find_ident_under_cursor((char_u **)&symbolp, FIND_IDENT);
    /* [normal.c] */
    if (len <= 0)
	return NULL;
    for (p=sniff_symbol; len; len--)
	*p++ = *symbolp++;
    *p = '\0';
    return sniff_symbol;
}