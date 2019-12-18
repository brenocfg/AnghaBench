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
typedef  int /*<<< orphan*/  uint8_t ;
struct gc_arena {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * make_base64_string2 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,struct gc_arena*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

uint8_t *
make_base64_string(const uint8_t *str, struct gc_arena *gc)
{
    return make_base64_string2(str, strlen((const char *)str), gc);
}