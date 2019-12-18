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
struct TYPE_4__ {scalar_t__* colors; } ;
struct TYPE_5__ {TYPE_1__ prefix; } ;
typedef  TYPE_2__ TrgmStateKey ;
typedef  scalar_t__ TrgmColor ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ COLOR_BLANK ; 
 scalar_t__ COLOR_UNKNOWN ; 

__attribute__((used)) static bool
validArcLabel(TrgmStateKey *key, TrgmColor co)
{
	/*
	 * We have to know full trigram in order to add outgoing arc.  So we can't
	 * do it if prefix is ambiguous.
	 */
	if (key->prefix.colors[0] == COLOR_UNKNOWN)
		return false;

	/* If key->prefix.colors[0] isn't unknown, its second color isn't either */
	Assert(key->prefix.colors[1] != COLOR_UNKNOWN);
	/* And we should not be called with an unknown arc color anytime */
	Assert(co != COLOR_UNKNOWN);

	/*
	 * We don't bother with making arcs representing three non-word
	 * characters, since that's useless for trigram extraction.
	 */
	if (key->prefix.colors[0] == COLOR_BLANK &&
		key->prefix.colors[1] == COLOR_BLANK &&
		co == COLOR_BLANK)
		return false;

	/*
	 * We also reject nonblank-blank-anything.  The nonblank-blank-nonblank
	 * case doesn't correspond to any trigram the trigram extraction code
	 * would make.  The nonblank-blank-blank case is also not possible with
	 * RPADDING = 1.  (Note that in many cases we'd fail to generate such a
	 * trigram even if it were valid, for example processing "foo bar" will
	 * not result in considering the trigram "o  ".  So if you want to support
	 * RPADDING = 2, there's more to do than just twiddle this test.)
	 */
	if (key->prefix.colors[0] != COLOR_BLANK &&
		key->prefix.colors[1] == COLOR_BLANK)
		return false;

	/*
	 * Other combinations involving blank are valid, in particular we assume
	 * blank-blank-nonblank is valid, which presumes that LPADDING is 2.
	 *
	 * Note: Using again the example "foo bar", we will not consider the
	 * trigram "  b", though this trigram would be found by the trigram
	 * extraction code.  Since we will find " ba", it doesn't seem worth
	 * trying to hack the algorithm to generate the additional trigram.
	 */

	/* arc label is valid */
	return true;
}