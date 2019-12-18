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
typedef  int /*<<< orphan*/  xmlChar ;
typedef  int /*<<< orphan*/  text ;

/* Variables and functions */
 scalar_t__ text_to_cstring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static xmlChar *
pgxml_texttoxmlchar(text *textstring)
{
	return (xmlChar *) text_to_cstring(textstring);
}