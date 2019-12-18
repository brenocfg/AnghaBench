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
struct colormap {int* classbits; } ;
typedef  scalar_t__ chr ;

/* Variables and functions */
 size_t CC_ALNUM ; 
 size_t CC_ALPHA ; 
 size_t CC_ASCII ; 
 size_t CC_BLANK ; 
 size_t CC_CNTRL ; 
 size_t CC_DIGIT ; 
 size_t CC_GRAPH ; 
 size_t CC_LOWER ; 
 size_t CC_PRINT ; 
 size_t CC_PUNCT ; 
 size_t CC_SPACE ; 
 size_t CC_UPPER ; 
 size_t CC_XDIGIT ; 
 scalar_t__ MAX_SIMPLE_CHR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ pg_wc_isalnum (scalar_t__) ; 
 scalar_t__ pg_wc_isalpha (scalar_t__) ; 
 scalar_t__ pg_wc_isdigit (scalar_t__) ; 
 scalar_t__ pg_wc_isgraph (scalar_t__) ; 
 scalar_t__ pg_wc_islower (scalar_t__) ; 
 scalar_t__ pg_wc_isprint (scalar_t__) ; 
 scalar_t__ pg_wc_ispunct (scalar_t__) ; 
 scalar_t__ pg_wc_isspace (scalar_t__) ; 
 scalar_t__ pg_wc_isupper (scalar_t__) ; 

__attribute__((used)) static int
cclass_column_index(struct colormap *cm, chr c)
{
	int			colnum = 0;

	/* Shouldn't go through all these pushups for simple chrs */
	assert(c > MAX_SIMPLE_CHR);

	/*
	 * Note: we should not see requests to consider cclasses that are not
	 * treated as locale-specific by cclass(), above.
	 */
	if (cm->classbits[CC_PRINT] && pg_wc_isprint(c))
		colnum |= cm->classbits[CC_PRINT];
	if (cm->classbits[CC_ALNUM] && pg_wc_isalnum(c))
		colnum |= cm->classbits[CC_ALNUM];
	if (cm->classbits[CC_ALPHA] && pg_wc_isalpha(c))
		colnum |= cm->classbits[CC_ALPHA];
	assert(cm->classbits[CC_ASCII] == 0);
	assert(cm->classbits[CC_BLANK] == 0);
	assert(cm->classbits[CC_CNTRL] == 0);
	if (cm->classbits[CC_DIGIT] && pg_wc_isdigit(c))
		colnum |= cm->classbits[CC_DIGIT];
	if (cm->classbits[CC_PUNCT] && pg_wc_ispunct(c))
		colnum |= cm->classbits[CC_PUNCT];
	assert(cm->classbits[CC_XDIGIT] == 0);
	if (cm->classbits[CC_SPACE] && pg_wc_isspace(c))
		colnum |= cm->classbits[CC_SPACE];
	if (cm->classbits[CC_LOWER] && pg_wc_islower(c))
		colnum |= cm->classbits[CC_LOWER];
	if (cm->classbits[CC_UPPER] && pg_wc_isupper(c))
		colnum |= cm->classbits[CC_UPPER];
	if (cm->classbits[CC_GRAPH] && pg_wc_isgraph(c))
		colnum |= cm->classbits[CC_GRAPH];

	return colnum;
}