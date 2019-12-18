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
typedef  int /*<<< orphan*/  uint8_t ;
struct csum_state {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ERRS (char*) ; 
 int ERR_FATAL ; 
 int /*<<< orphan*/  csum_update (int /*<<< orphan*/ *,size_t,struct csum_state*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ *) ; 

int
write_out_data(FILE *outfile, uint8_t *data, size_t len,
		struct csum_state *css)
{
	errno = 0;

	fwrite(data, len, 1, outfile);
	if (errno) {
		ERRS("unable to write output file");
		return ERR_FATAL;
	}

	if (css) {
		csum_update(data, len, css);
	}

	return 0;
}