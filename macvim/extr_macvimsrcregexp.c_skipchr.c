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
 int /*<<< orphan*/  FALSE ; 
 char NUL ; 
 int /*<<< orphan*/  at_start ; 
 int curchr ; 
 int nextchr ; 
 int /*<<< orphan*/  prev_at_start ; 
 int prevchr ; 
 size_t prevchr_len ; 
 int prevprevchr ; 
 char* regparse ; 

__attribute__((used)) static void
skipchr()
{
    /* peekchr() eats a backslash, do the same here */
    if (*regparse == '\\')
	prevchr_len = 1;
    else
	prevchr_len = 0;
    if (regparse[prevchr_len] != NUL)
    {
#ifdef FEAT_MBYTE
	if (enc_utf8)
	    /* exclude composing chars that mb_ptr2len does include */
	    prevchr_len += utf_ptr2len(regparse + prevchr_len);
	else if (has_mbyte)
	    prevchr_len += (*mb_ptr2len)(regparse + prevchr_len);
	else
#endif
	    ++prevchr_len;
    }
    regparse += prevchr_len;
    prev_at_start = at_start;
    at_start = FALSE;
    prevprevchr = prevchr;
    prevchr = curchr;
    curchr = nextchr;	    /* use previously unget char, or -1 */
    nextchr = -1;
}