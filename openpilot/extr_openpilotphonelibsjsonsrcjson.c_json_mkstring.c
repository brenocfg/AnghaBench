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
typedef  int /*<<< orphan*/  JsonNode ;

/* Variables and functions */
 int /*<<< orphan*/  json_strdup (char const*) ; 
 int /*<<< orphan*/ * mkstring (int /*<<< orphan*/ ) ; 

JsonNode *json_mkstring(const char *s)
{
	return mkstring(json_strdup(s));
}