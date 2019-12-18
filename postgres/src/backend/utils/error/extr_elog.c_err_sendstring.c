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
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 scalar_t__ in_error_recursion_trouble () ; 
 int /*<<< orphan*/  pq_send_ascii_string (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pq_sendstring (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
err_sendstring(StringInfo buf, const char *str)
{
	if (in_error_recursion_trouble())
		pq_send_ascii_string(buf, str);
	else
		pq_sendstring(buf, str);
}