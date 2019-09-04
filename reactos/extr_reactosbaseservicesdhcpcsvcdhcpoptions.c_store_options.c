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
struct tree_cache {int len; scalar_t__ value; } ;
typedef  int /*<<< orphan*/  option_stored ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,unsigned char) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

int
store_options(unsigned char *buffer, int buflen, struct tree_cache **options,
    unsigned char *priority_list, int priority_len, int first_cutoff,
    int second_cutoff)
{
	int bufix = 0, option_stored[256], i, ix;

	/* Zero out the stored-lengths array. */
	memset(option_stored, 0, sizeof(option_stored));

	/*
	 * Copy out the options in the order that they appear in the
	 * priority list...
	 */
	for (i = 0; i < priority_len; i++) {
		/* Code for next option to try to store. */
		int code = priority_list[i];
		int optstart;

		/*
		 * Number of bytes left to store (some may already have
		 * been stored by a previous pass).
		 */
		int length;

		/* If no data is available for this option, skip it. */
		if (!options[code]) {
			continue;
		}

		/*
		 * The client could ask for things that are mandatory,
		 * in which case we should avoid storing them twice...
		 */
		if (option_stored[code])
			continue;
		option_stored[code] = 1;

		/* We should now have a constant length for the option. */
		length = options[code]->len;

		/* Try to store the option. */

		/*
		 * If the option's length is more than 255, we must
		 * store it in multiple hunks.   Store 255-byte hunks
		 * first.  However, in any case, if the option data will
		 * cross a buffer boundary, split it across that
		 * boundary.
		 */
		ix = 0;

		optstart = bufix;
		while (length) {
			unsigned char incr = length > 255 ? 255 : length;

			/*
			 * If this hunk of the buffer will cross a
			 * boundary, only go up to the boundary in this
			 * pass.
			 */
			if (bufix < first_cutoff &&
			    bufix + incr > first_cutoff)
				incr = first_cutoff - bufix;
			else if (bufix < second_cutoff &&
			    bufix + incr > second_cutoff)
				incr = second_cutoff - bufix;

			/*
			 * If this option is going to overflow the
			 * buffer, skip it.
			 */
			if (bufix + 2 + incr > buflen) {
				bufix = optstart;
				break;
			}

			/* Everything looks good - copy it in! */
			buffer[bufix] = code;
			buffer[bufix + 1] = incr;
			memcpy(buffer + bufix + 2,
			   options[code]->value + ix, incr);
			length -= incr;
			ix += incr;
			bufix += 2 + incr;
		}
	}
	return (bufix);
}