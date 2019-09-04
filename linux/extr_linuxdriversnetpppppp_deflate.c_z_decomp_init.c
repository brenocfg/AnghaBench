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
struct ppp_deflate_state {scalar_t__ w_size; int unit; int debug; int mru; int /*<<< orphan*/  strm; scalar_t__ seqno; } ;

/* Variables and functions */
 int CILEN_DEFLATE ; 
 unsigned char CI_DEFLATE ; 
 unsigned char CI_DEFLATE_DRAFT ; 
 unsigned char DEFLATE_CHK_SEQUENCE ; 
 scalar_t__ DEFLATE_METHOD (unsigned char) ; 
 scalar_t__ DEFLATE_METHOD_VAL ; 
 scalar_t__ DEFLATE_SIZE (unsigned char) ; 
 int /*<<< orphan*/  zlib_inflateReset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int z_decomp_init(void *arg, unsigned char *options, int opt_len,
			 int unit, int hdrlen, int mru, int debug)
{
	struct ppp_deflate_state *state = (struct ppp_deflate_state *) arg;

	if (opt_len < CILEN_DEFLATE ||
	    (options[0] != CI_DEFLATE && options[0] != CI_DEFLATE_DRAFT) ||
	    options[1] != CILEN_DEFLATE ||
	    DEFLATE_METHOD(options[2]) != DEFLATE_METHOD_VAL ||
	    DEFLATE_SIZE(options[2]) != state->w_size ||
	    options[3] != DEFLATE_CHK_SEQUENCE)
		return 0;

	state->seqno = 0;
	state->unit  = unit;
	state->debug = debug;
	state->mru   = mru;

	zlib_inflateReset(&state->strm);

	return 1;
}