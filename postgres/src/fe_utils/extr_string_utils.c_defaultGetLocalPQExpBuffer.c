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
typedef  int /*<<< orphan*/ * PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/ * createPQExpBuffer () ; 
 int /*<<< orphan*/  resetPQExpBuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PQExpBuffer
defaultGetLocalPQExpBuffer(void)
{
	static PQExpBuffer id_return = NULL;

	if (id_return)				/* first time through? */
	{
		/* same buffer, just wipe contents */
		resetPQExpBuffer(id_return);
	}
	else
	{
		/* new buffer */
		id_return = createPQExpBuffer();
	}

	return id_return;
}