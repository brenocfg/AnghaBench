#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32 ;
struct TYPE_6__ {size_t dec_index; scalar_t__ codepoint; } ;
typedef  TYPE_1__ pg_unicode_decomposition ;

/* Variables and functions */
 scalar_t__ DECOMPOSITION_NO_COMPOSE (TYPE_1__ const*) ; 
 int DECOMPOSITION_SIZE (TYPE_1__ const*) ; 
 scalar_t__ LBASE ; 
 scalar_t__ LCOUNT ; 
 scalar_t__ SBASE ; 
 scalar_t__ SCOUNT ; 
 scalar_t__ TBASE ; 
 scalar_t__ TCOUNT ; 
 TYPE_1__* UnicodeDecompMain ; 
 scalar_t__* UnicodeDecomp_codepoints ; 
 scalar_t__ VBASE ; 
 scalar_t__ VCOUNT ; 
 int lengthof (TYPE_1__*) ; 

__attribute__((used)) static bool
recompose_code(uint32 start, uint32 code, uint32 *result)
{
	/*
	 * Handle Hangul characters algorithmically, per the Unicode spec.
	 *
	 * Check if two current characters are L and V.
	 */
	if (start >= LBASE && start < LBASE + LCOUNT &&
		code >= VBASE && code < VBASE + VCOUNT)
	{
		/* make syllable of form LV */
		uint32		lindex = start - LBASE;
		uint32		vindex = code - VBASE;

		*result = SBASE + (lindex * VCOUNT + vindex) * TCOUNT;
		return true;
	}
	/* Check if two current characters are LV and T */
	else if (start >= SBASE && start < (SBASE + SCOUNT) &&
			 ((start - SBASE) % TCOUNT) == 0 &&
			 code >= TBASE && code < (TBASE + TCOUNT))
	{
		/* make syllable of form LVT */
		uint32		tindex = code - TBASE;

		*result = start + tindex;
		return true;
	}
	else
	{
		int			i;

		/*
		 * Do an inverse lookup of the decomposition tables to see if anything
		 * matches. The comparison just needs to be a perfect match on the
		 * sub-table of size two, because the start character has already been
		 * recomposed partially.
		 */
		for (i = 0; i < lengthof(UnicodeDecompMain); i++)
		{
			const pg_unicode_decomposition *entry = &UnicodeDecompMain[i];

			if (DECOMPOSITION_SIZE(entry) != 2)
				continue;

			if (DECOMPOSITION_NO_COMPOSE(entry))
				continue;

			if (start == UnicodeDecomp_codepoints[entry->dec_index] &&
				code == UnicodeDecomp_codepoints[entry->dec_index + 1])
			{
				*result = entry->codepoint;
				return true;
			}
		}
	}

	return false;
}