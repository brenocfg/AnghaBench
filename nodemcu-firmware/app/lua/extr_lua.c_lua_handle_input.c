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
struct TYPE_4__ {int /*<<< orphan*/  line; int /*<<< orphan*/  len; int /*<<< orphan*/  line_position; int /*<<< orphan*/  firstline; scalar_t__ L; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODE_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dojob (TYPE_1__*) ; 
 TYPE_1__ gLoad ; 
 scalar_t__ readline (TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void lua_handle_input (bool force)
{
  while (gLoad.L && (force || readline (&gLoad))) {
    NODE_DBG("Handle Input: first=%u, pos=%u, len=%u, actual=%u, line=%s\n", gLoad.firstline,
              gLoad.line_position, gLoad.len, strlen(gLoad.line), gLoad.line);
    dojob (&gLoad);
    force = false;
  }
}