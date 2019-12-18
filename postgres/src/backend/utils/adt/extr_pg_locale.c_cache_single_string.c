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

/* Variables and functions */
 char* MemoryContextStrdup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/  pfree (char*) ; 
 char* pg_any_to_server (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
cache_single_string(char **dst, const char *src, int encoding)
{
	char	   *ptr;
	char	   *olddst;

	/* Convert the string to the database encoding, or validate it's OK */
	ptr = pg_any_to_server(src, strlen(src), encoding);

	/* Store the string in long-lived storage, replacing any previous value */
	olddst = *dst;
	*dst = MemoryContextStrdup(TopMemoryContext, ptr);
	if (olddst)
		pfree(olddst);

	/* Might as well clean up any palloc'd conversion result, too */
	if (ptr != src)
		pfree(ptr);
}