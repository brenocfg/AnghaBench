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
struct TYPE_4__ {char cursor; } ;
typedef  TYPE_1__* StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 

void
pq_beginmessage(StringInfo buf, char msgtype)
{
	initStringInfo(buf);

	/*
	 * We stash the message type into the buffer's cursor field, expecting
	 * that the pq_sendXXX routines won't touch it.  We could alternatively
	 * make it the first byte of the buffer contents, but this seems easier.
	 */
	buf->cursor = msgtype;
}