#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int clocations_count; int highest_extern_param_id; TYPE_1__* clocations; } ;
typedef  TYPE_2__ pgssJumbleState ;
struct TYPE_5__ {int location; int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  fill_in_constant_lengths (TYPE_2__*,char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* palloc (int) ; 
 scalar_t__ sprintf (char*,char*,int) ; 

__attribute__((used)) static char *
generate_normalized_query(pgssJumbleState *jstate, const char *query,
						  int query_loc, int *query_len_p, int encoding)
{
	char	   *norm_query;
	int			query_len = *query_len_p;
	int			i,
				norm_query_buflen,	/* Space allowed for norm_query */
				len_to_wrt,		/* Length (in bytes) to write */
				quer_loc = 0,	/* Source query byte location */
				n_quer_loc = 0, /* Normalized query byte location */
				last_off = 0,	/* Offset from start for previous tok */
				last_tok_len = 0;	/* Length (in bytes) of that tok */

	/*
	 * Get constants' lengths (core system only gives us locations).  Note
	 * this also ensures the items are sorted by location.
	 */
	fill_in_constant_lengths(jstate, query, query_loc);

	/*
	 * Allow for $n symbols to be longer than the constants they replace.
	 * Constants must take at least one byte in text form, while a $n symbol
	 * certainly isn't more than 11 bytes, even if n reaches INT_MAX.  We
	 * could refine that limit based on the max value of n for the current
	 * query, but it hardly seems worth any extra effort to do so.
	 */
	norm_query_buflen = query_len + jstate->clocations_count * 10;

	/* Allocate result buffer */
	norm_query = palloc(norm_query_buflen + 1);

	for (i = 0; i < jstate->clocations_count; i++)
	{
		int			off,		/* Offset from start for cur tok */
					tok_len;	/* Length (in bytes) of that tok */

		off = jstate->clocations[i].location;
		/* Adjust recorded location if we're dealing with partial string */
		off -= query_loc;

		tok_len = jstate->clocations[i].length;

		if (tok_len < 0)
			continue;			/* ignore any duplicates */

		/* Copy next chunk (what precedes the next constant) */
		len_to_wrt = off - last_off;
		len_to_wrt -= last_tok_len;

		Assert(len_to_wrt >= 0);
		memcpy(norm_query + n_quer_loc, query + quer_loc, len_to_wrt);
		n_quer_loc += len_to_wrt;

		/* And insert a param symbol in place of the constant token */
		n_quer_loc += sprintf(norm_query + n_quer_loc, "$%d",
							  i + 1 + jstate->highest_extern_param_id);

		quer_loc = off + tok_len;
		last_off = off;
		last_tok_len = tok_len;
	}

	/*
	 * We've copied up until the last ignorable constant.  Copy over the
	 * remaining bytes of the original query string.
	 */
	len_to_wrt = query_len - quer_loc;

	Assert(len_to_wrt >= 0);
	memcpy(norm_query + n_quer_loc, query + quer_loc, len_to_wrt);
	n_quer_loc += len_to_wrt;

	Assert(n_quer_loc <= norm_query_buflen);
	norm_query[n_quer_loc] = '\0';

	*query_len_p = n_quer_loc;
	return norm_query;
}