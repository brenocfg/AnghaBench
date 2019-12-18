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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_5__ {scalar_t__ maxlen; scalar_t__ len; size_t data; } ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  enlargePQExpBuffer (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  markPQExpBufferBroken (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 
 int vsnprintf (size_t,size_t,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
appendPQExpBufferVA(PQExpBuffer str, const char *fmt, va_list args)
{
	size_t		avail;
	size_t		needed;
	int			nprinted;

	/*
	 * Try to format the given string into the available space; but if there's
	 * hardly any space, don't bother trying, just enlarge the buffer first.
	 */
	if (str->maxlen > str->len + 16)
	{
		avail = str->maxlen - str->len;

		nprinted = vsnprintf(str->data + str->len, avail, fmt, args);

		/*
		 * If vsnprintf reports an error, fail (we assume this means there's
		 * something wrong with the format string).
		 */
		if (unlikely(nprinted < 0))
		{
			markPQExpBufferBroken(str);
			return true;
		}

		if ((size_t) nprinted < avail)
		{
			/* Success.  Note nprinted does not include trailing null. */
			str->len += nprinted;
			return true;
		}

		/*
		 * We assume a C99-compliant vsnprintf, so believe its estimate of the
		 * required space, and add one for the trailing null.  (If it's wrong,
		 * the logic will still work, but we may loop multiple times.)
		 *
		 * Choke if the required space would exceed INT_MAX, since str->maxlen
		 * can't represent more than that.
		 */
		if (unlikely(nprinted > INT_MAX - 1))
		{
			markPQExpBufferBroken(str);
			return true;
		}
		needed = nprinted + 1;
	}
	else
	{
		/*
		 * We have to guess at how much to enlarge, since we're skipping the
		 * formatting work.  Fortunately, because of enlargePQExpBuffer's
		 * preference for power-of-2 sizes, this number isn't very sensitive;
		 * the net effect is that we'll double the buffer size before trying
		 * to run vsnprintf, which seems sensible.
		 */
		needed = 32;
	}

	/* Increase the buffer size and try again. */
	if (!enlargePQExpBuffer(str, needed))
		return true;			/* oops, out of memory */

	return false;
}