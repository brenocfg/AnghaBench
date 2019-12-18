#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xa_state {int xa_index; int /*<<< orphan*/ * xa_node; int /*<<< orphan*/  xa; } ;
struct TYPE_2__ {int shift; } ;

/* Variables and functions */
 int XA_CHUNK_MASK ; 
 void* set_bounds (struct xa_state*) ; 
 void* xa_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_is_node (void*) ; 
 TYPE_1__* xa_to_node (void*) ; 
 scalar_t__ xas_error (struct xa_state*) ; 
 void* xas_reload (struct xa_state*) ; 
 scalar_t__ xas_valid (struct xa_state*) ; 

__attribute__((used)) static void *xas_start(struct xa_state *xas)
{
	void *entry;

	if (xas_valid(xas))
		return xas_reload(xas);
	if (xas_error(xas))
		return NULL;

	entry = xa_head(xas->xa);
	if (!xa_is_node(entry)) {
		if (xas->xa_index)
			return set_bounds(xas);
	} else {
		if ((xas->xa_index >> xa_to_node(entry)->shift) > XA_CHUNK_MASK)
			return set_bounds(xas);
	}

	xas->xa_node = NULL;
	return entry;
}