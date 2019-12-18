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
struct path {scalar_t__ flags; scalar_t__ num_keys; int /*<<< orphan*/ * keys; scalar_t__ len_class; int /*<<< orphan*/ * class; scalar_t__ num_namespaces; int /*<<< orphan*/ * len_namespaces; int /*<<< orphan*/ * namespaces; scalar_t__ len_server; int /*<<< orphan*/ * server; scalar_t__ len_text; int /*<<< orphan*/ * text; } ;

/* Variables and functions */

__attribute__((used)) static void init_path( struct path *path )
{
    path->text           = NULL;
    path->len_text       = 0;
    path->server         = NULL;
    path->len_server     = 0;
    path->namespaces     = NULL;
    path->len_namespaces = NULL;
    path->num_namespaces = 0;
    path->class          = NULL;
    path->len_class      = 0;
    path->keys           = NULL;
    path->num_keys       = 0;
    path->flags          = 0;
}