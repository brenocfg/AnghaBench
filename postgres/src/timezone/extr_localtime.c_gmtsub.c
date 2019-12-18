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
struct state {int /*<<< orphan*/  chars; } ;
struct pg_tm {int /*<<< orphan*/  tm_zone; } ;
typedef  int /*<<< orphan*/  pg_time_t ;
typedef  scalar_t__ int32 ;

/* Variables and functions */
 int /*<<< orphan*/  gmtload (struct state*) ; 
 scalar_t__ malloc (int) ; 
 struct pg_tm* timesub (int /*<<< orphan*/  const*,scalar_t__,struct state*,struct pg_tm*) ; 
 int /*<<< orphan*/  wildabbr ; 

__attribute__((used)) static struct pg_tm *
gmtsub(pg_time_t const *timep, int32 offset,
	   struct pg_tm *tmp)
{
	struct pg_tm *result;

	/* GMT timezone state data is kept here */
	static struct state *gmtptr = NULL;

	if (gmtptr == NULL)
	{
		/* Allocate on first use */
		gmtptr = (struct state *) malloc(sizeof(struct state));
		if (gmtptr == NULL)
			return NULL;		/* errno should be set by malloc */
		gmtload(gmtptr);
	}

	result = timesub(timep, offset, gmtptr, tmp);

	/*
	 * Could get fancy here and deliver something such as "+xx" or "-xx" if
	 * offset is non-zero, but this is no time for a treasure hunt.
	 */
	if (offset != 0)
		tmp->tm_zone = wildabbr;
	else
		tmp->tm_zone = gmtptr->chars;

	return result;
}