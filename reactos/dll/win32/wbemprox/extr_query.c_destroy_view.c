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
struct view {struct view* result; scalar_t__ table; } ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (struct view*) ; 
 int /*<<< orphan*/  release_table (scalar_t__) ; 

void destroy_view( struct view *view )
{
    if (!view) return;
    if (view->table) release_table( view->table );
    heap_free( view->result );
    heap_free( view );
}