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
struct trace_entry {scalar_t__ data; int /*<<< orphan*/  type; } ;
struct trace_buffer {int dummy; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  TRACE_TYPE_STRING ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 struct trace_entry* trace_alloc_entry (struct trace_buffer*,int) ; 

int trace_log_string(struct trace_buffer *tb, char *str)
{
	struct trace_entry *e;
	char *p;
	int len;

	len = strlen(str);

	/* We NULL terminate to make printing easier */
	e = trace_alloc_entry(tb, len + 1);
	if (!e)
		return -ENOSPC;

	e->type = TRACE_TYPE_STRING;
	p = (char *)e->data;
	memcpy(p, str, len);
	p += len;
	*p = '\0';

	return 0;
}