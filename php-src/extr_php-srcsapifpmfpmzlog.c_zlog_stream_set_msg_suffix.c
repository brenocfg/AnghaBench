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
typedef  int /*<<< orphan*/  zlog_bool ;
struct zlog_stream {int msg_suffix_len; int msg_final_suffix_len; int /*<<< orphan*/ * msg_final_suffix; int /*<<< orphan*/ * msg_suffix; int /*<<< orphan*/  decorate; int /*<<< orphan*/  wrap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZLOG_FALSE ; 
 int /*<<< orphan*/  ZLOG_TRUE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,size_t) ; 
 void* strlen (char const*) ; 

zlog_bool zlog_stream_set_msg_suffix(
		struct zlog_stream *stream, const char *suffix, const char *final_suffix)  /* {{{ */
{
	size_t len;
	if (!stream->wrap || !stream->decorate) {
		return ZLOG_TRUE;
	}

	if (suffix != NULL && final_suffix != NULL) {
		stream->msg_suffix_len = strlen(suffix);
		stream->msg_final_suffix_len = strlen(final_suffix);
		len = stream->msg_suffix_len + stream->msg_final_suffix_len + 2;
		if (stream->msg_suffix != NULL) {
			free(stream->msg_suffix);
		}
		stream->msg_suffix = malloc(len);
		if (stream->msg_suffix == NULL) {
			return ZLOG_FALSE;
		}
		stream->msg_final_suffix = stream->msg_suffix + stream->msg_suffix_len + 1;
		memcpy(stream->msg_suffix, suffix, stream->msg_suffix_len + 1);
		memcpy(stream->msg_final_suffix, final_suffix, stream->msg_final_suffix_len + 1);
		return ZLOG_TRUE;
	}
	if (suffix != NULL) {
		stream->msg_suffix_len = strlen(suffix);
		len = stream->msg_suffix_len + 1;
		stream->msg_suffix = malloc(len);
		if (stream->msg_suffix != NULL) {
			free(stream->msg_suffix);
		}
		if (stream->msg_suffix == NULL) {
			return ZLOG_FALSE;
		}
		memcpy(stream->msg_suffix, suffix, len);
		return ZLOG_TRUE;
	}
	if (final_suffix != NULL) {
		stream->msg_final_suffix_len = strlen(final_suffix);
		len = stream->msg_final_suffix_len + 1;
		stream->msg_final_suffix = malloc(len);
		if (stream->msg_final_suffix != NULL) {
			free(stream->msg_suffix);
		}
		if (stream->msg_final_suffix == NULL) {
			return ZLOG_FALSE;
		}
		memcpy(stream->msg_final_suffix, final_suffix, len);
		return ZLOG_TRUE;
	}

	return ZLOG_TRUE;
}