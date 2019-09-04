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
struct buffer_ext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_ext_add (struct buffer_ext*,void*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void emit_string(struct buffer_ext *be, const char *s)
{
	buffer_ext_add(be, (void *)s, strlen(s) + 1);
}