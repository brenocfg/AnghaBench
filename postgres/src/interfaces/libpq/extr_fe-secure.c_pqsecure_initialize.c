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
typedef  int /*<<< orphan*/  PGconn ;

/* Variables and functions */
 int pgtls_init (int /*<<< orphan*/ *) ; 

int
pqsecure_initialize(PGconn *conn)
{
	int			r = 0;

#ifdef USE_SSL
	r = pgtls_init(conn);
#endif

	return r;
}