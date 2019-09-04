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
struct marker {int type; char* ref; int /*<<< orphan*/ * next; int /*<<< orphan*/  offset; } ;
struct data {int /*<<< orphan*/  len; } ;
typedef  enum markertype { ____Placeholder_markertype } markertype ;

/* Variables and functions */
 struct data data_append_markers (struct data,struct marker*) ; 
 struct marker* xmalloc (int) ; 

struct data data_add_marker(struct data d, enum markertype type, char *ref)
{
	struct marker *m;

	m = xmalloc(sizeof(*m));
	m->offset = d.len;
	m->type = type;
	m->ref = ref;
	m->next = NULL;

	return data_append_markers(d, m);
}