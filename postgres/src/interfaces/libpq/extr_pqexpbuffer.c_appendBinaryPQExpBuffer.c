#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* data; int len; } ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  enlargePQExpBuffer (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

void
appendBinaryPQExpBuffer(PQExpBuffer str, const char *data, size_t datalen)
{
	/* Make more room if needed */
	if (!enlargePQExpBuffer(str, datalen))
		return;

	/* OK, append the data */
	memcpy(str->data + str->len, data, datalen);
	str->len += datalen;

	/*
	 * Keep a trailing null in place, even though it's probably useless for
	 * binary data...
	 */
	str->data[str->len] = '\0';
}