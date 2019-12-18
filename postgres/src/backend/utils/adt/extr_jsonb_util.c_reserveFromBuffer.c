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
struct TYPE_4__ {int len; char* data; } ;
typedef  TYPE_1__* StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  enlargeStringInfo (TYPE_1__*,int) ; 

__attribute__((used)) static int
reserveFromBuffer(StringInfo buffer, int len)
{
	int			offset;

	/* Make more room if needed */
	enlargeStringInfo(buffer, len);

	/* remember current offset */
	offset = buffer->len;

	/* reserve the space */
	buffer->len += len;

	/*
	 * Keep a trailing null in place, even though it's not useful for us; it
	 * seems best to preserve the invariants of StringInfos.
	 */
	buffer->data[buffer->len] = '\0';

	return offset;
}