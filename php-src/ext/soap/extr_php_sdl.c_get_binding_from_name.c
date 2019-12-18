#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ smart_str ;
typedef  TYPE_2__* sdlPtr ;
typedef  int /*<<< orphan*/  sdlBindingPtr ;
struct TYPE_9__ {int /*<<< orphan*/  bindings; } ;

/* Variables and functions */
 int /*<<< orphan*/  smart_str_0 (TYPE_1__*) ; 
 int /*<<< orphan*/  smart_str_appendc (TYPE_1__*,char) ; 
 int /*<<< orphan*/  smart_str_appends (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  smart_str_free (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_hash_find_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

sdlBindingPtr get_binding_from_name(sdlPtr sdl, char *name, char *ns)
{
	sdlBindingPtr binding;
	smart_str key = {0};

	smart_str_appends(&key, ns);
	smart_str_appendc(&key, ':');
	smart_str_appends(&key, name);
	smart_str_0(&key);

	binding = zend_hash_find_ptr(sdl->bindings, key.s);

	smart_str_free(&key);
	return binding;
}