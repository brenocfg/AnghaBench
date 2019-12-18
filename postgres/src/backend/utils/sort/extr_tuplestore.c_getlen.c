#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  len ;
struct TYPE_3__ {int /*<<< orphan*/  myfile; } ;
typedef  TYPE_1__ Tuplestorestate ;

/* Variables and functions */
 size_t BufFileRead (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static unsigned int
getlen(Tuplestorestate *state, bool eofOK)
{
	unsigned int len;
	size_t		nbytes;

	nbytes = BufFileRead(state->myfile, (void *) &len, sizeof(len));
	if (nbytes == sizeof(len))
		return len;
	if (nbytes != 0 || !eofOK)
		ereport(ERROR,
				(errcode_for_file_access(),
				 errmsg("could not read from tuplestore temporary file: %m")));
	return 0;
}