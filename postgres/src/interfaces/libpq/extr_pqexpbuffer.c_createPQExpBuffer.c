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
typedef  int /*<<< orphan*/  PQExpBufferData ;
typedef  int /*<<< orphan*/ * PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  initPQExpBuffer (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 

PQExpBuffer
createPQExpBuffer(void)
{
	PQExpBuffer res;

	res = (PQExpBuffer) malloc(sizeof(PQExpBufferData));
	if (res != NULL)
		initPQExpBuffer(res);

	return res;
}