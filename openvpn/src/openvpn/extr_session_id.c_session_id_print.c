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
struct session_id {int /*<<< orphan*/  id; } ;
struct gc_arena {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SID_SIZE ; 
 char const* format_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gc_arena*) ; 

const char *
session_id_print(const struct session_id *sid, struct gc_arena *gc)
{
    return format_hex(sid->id, SID_SIZE, 0, gc);
}