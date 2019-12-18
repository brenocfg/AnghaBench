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
struct magic_set {int dummy; } ;

/* Variables and functions */
 int file_buffer (struct magic_set*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const*,size_t) ; 
 char const* file_getbuffer (struct magic_set*) ; 
 int file_reset (struct magic_set*,int) ; 

const char *
magic_buffer(struct magic_set *ms, const void *buf, size_t nb)
{
	if (ms == NULL)
		return NULL;
	if (file_reset(ms, 1) == -1)
		return NULL;
	/*
	 * The main work is done here!
	 * We have the file name and/or the data buffer to be identified.
	 */
	if (file_buffer(ms, NULL, NULL, NULL, buf, nb) == -1) {
		return NULL;
	}
	return file_getbuffer(ms);
}