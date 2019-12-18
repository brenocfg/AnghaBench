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
 int pg_mbcliplen (char*,int,scalar_t__) ; 
 scalar_t__ pgstat_track_activity_query_size ; 
 char* pnstrdup (char const*,scalar_t__) ; 
 int strlen (char*) ; 

char *
pgstat_clip_activity(const char *raw_activity)
{
	char	   *activity;
	int			rawlen;
	int			cliplen;

	/*
	 * Some callers, like pgstat_get_backend_current_activity(), do not
	 * guarantee that the buffer isn't concurrently modified. We try to take
	 * care that the buffer is always terminated by a NUL byte regardless, but
	 * let's still be paranoid about the string's length. In those cases the
	 * underlying buffer is guaranteed to be pgstat_track_activity_query_size
	 * large.
	 */
	activity = pnstrdup(raw_activity, pgstat_track_activity_query_size - 1);

	/* now double-guaranteed to be NUL terminated */
	rawlen = strlen(activity);

	/*
	 * All supported server-encodings make it possible to determine the length
	 * of a multi-byte character from its first byte (this is not the case for
	 * client encodings, see GB18030). As st_activity is always stored using
	 * server encoding, this allows us to perform multi-byte aware truncation,
	 * even if the string earlier was truncated in the middle of a multi-byte
	 * character.
	 */
	cliplen = pg_mbcliplen(activity, rawlen,
						   pgstat_track_activity_query_size - 1);

	activity[cliplen] = '\0';

	return activity;
}