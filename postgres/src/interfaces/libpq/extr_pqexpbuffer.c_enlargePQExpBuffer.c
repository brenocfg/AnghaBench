#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t len; size_t maxlen; char* data; } ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 scalar_t__ PQExpBufferBroken (TYPE_1__*) ; 
 int /*<<< orphan*/  markPQExpBufferBroken (TYPE_1__*) ; 
 scalar_t__ realloc (char*,size_t) ; 

int
enlargePQExpBuffer(PQExpBuffer str, size_t needed)
{
	size_t		newlen;
	char	   *newdata;

	if (PQExpBufferBroken(str))
		return 0;				/* already failed */

	/*
	 * Guard against ridiculous "needed" values, which can occur if we're fed
	 * bogus data.  Without this, we can get an overflow or infinite loop in
	 * the following.
	 */
	if (needed >= ((size_t) INT_MAX - str->len))
	{
		markPQExpBufferBroken(str);
		return 0;
	}

	needed += str->len + 1;		/* total space required now */

	/* Because of the above test, we now have needed <= INT_MAX */

	if (needed <= str->maxlen)
		return 1;				/* got enough space already */

	/*
	 * We don't want to allocate just a little more space with each append;
	 * for efficiency, double the buffer size each time it overflows.
	 * Actually, we might need to more than double it if 'needed' is big...
	 */
	newlen = (str->maxlen > 0) ? (2 * str->maxlen) : 64;
	while (needed > newlen)
		newlen = 2 * newlen;

	/*
	 * Clamp to INT_MAX in case we went past it.  Note we are assuming here
	 * that INT_MAX <= UINT_MAX/2, else the above loop could overflow.  We
	 * will still have newlen >= needed.
	 */
	if (newlen > (size_t) INT_MAX)
		newlen = (size_t) INT_MAX;

	newdata = (char *) realloc(str->data, newlen);
	if (newdata != NULL)
	{
		str->data = newdata;
		str->maxlen = newlen;
		return 1;
	}

	markPQExpBufferBroken(str);
	return 0;
}