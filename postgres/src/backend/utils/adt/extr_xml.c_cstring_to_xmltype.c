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
typedef  int /*<<< orphan*/  xmltype ;

/* Variables and functions */
 scalar_t__ cstring_to_text (char const*) ; 

__attribute__((used)) static xmltype *
cstring_to_xmltype(const char *string)
{
	return (xmltype *) cstring_to_text(string);
}