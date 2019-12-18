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

/* Variables and functions */
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 scalar_t__ uri_prefix_length (char const*) ; 

__attribute__((used)) static bool
recognized_connection_string(const char *connstr)
{
	return uri_prefix_length(connstr) != 0 || strchr(connstr, '=') != NULL;
}