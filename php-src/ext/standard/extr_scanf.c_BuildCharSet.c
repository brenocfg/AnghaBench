#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct Range {char start; char end; } ;
struct TYPE_4__ {int exclude; char* chars; size_t nchars; size_t nranges; struct Range* ranges; } ;
typedef  TYPE_1__ CharSet ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ safe_emalloc (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char * BuildCharSet(CharSet *cset, char *format)
{
	char *ch, start;
	int  nranges;
	char *end;

	memset(cset, 0, sizeof(CharSet));

	ch = format;
	if (*ch == '^') {
		cset->exclude = 1;
		ch = ++format;
	}
	end = format + 1;	/* verify this - cc */

	/*
	 * Find the close bracket so we can overallocate the set.
	 */
	if (*ch == ']') {
		ch = end++;
	}
	nranges = 0;
	while (*ch != ']') {
		if (*ch == '-') {
			nranges++;
		}
		ch = end++;
	}

	cset->chars = (char *) safe_emalloc(sizeof(char), (end - format - 1), 0);
	if (nranges > 0) {
		cset->ranges = (struct Range *) safe_emalloc(sizeof(struct Range), nranges, 0);
	} else {
		cset->ranges = NULL;
	}

	/*
	 * Now build the character set.
	 */
	cset->nchars = cset->nranges = 0;
	ch    = format++;
	start = *ch;
	if (*ch == ']' || *ch == '-') {
		cset->chars[cset->nchars++] = *ch;
		ch = format++;
	}
	while (*ch != ']') {
		if (*format == '-') {
			/*
			 * This may be the first character of a range, so don't add
			 * it yet.
			 */
			start = *ch;
		} else if (*ch == '-') {
			/*
			 * Check to see if this is the last character in the set, in which
			 * case it is not a range and we should add the previous character
			 * as well as the dash.
			 */
			if (*format == ']') {
				cset->chars[cset->nchars++] = start;
				cset->chars[cset->nchars++] = *ch;
			} else {
				ch = format++;

				/*
				 * Check to see if the range is in reverse order.
				 */
				if (start < *ch) {
					cset->ranges[cset->nranges].start = start;
					cset->ranges[cset->nranges].end = *ch;
				} else {
					cset->ranges[cset->nranges].start = *ch;
					cset->ranges[cset->nranges].end = start;
				}
				cset->nranges++;
			}
		} else {
			cset->chars[cset->nchars++] = *ch;
		}
		ch = format++;
	}
	return format;
}