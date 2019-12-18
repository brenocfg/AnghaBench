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
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* PQExpBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  appendPQExpBufferStr (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
copy_previous_query(PQExpBuffer query_buf, PQExpBuffer previous_buf)
{
	if (query_buf && query_buf->len == 0)
		appendPQExpBufferStr(query_buf, previous_buf->data);
}