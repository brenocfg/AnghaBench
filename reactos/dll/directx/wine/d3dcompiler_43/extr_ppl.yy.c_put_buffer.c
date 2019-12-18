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
 int /*<<< orphan*/  add_text_to_macro (char const*,int) ; 
 scalar_t__ top_macro () ; 
 int /*<<< orphan*/  wpp_write (char const*,int) ; 

__attribute__((used)) static void put_buffer(const char *s, int len)
{
	if(top_macro())
		add_text_to_macro(s, len);
	else
		wpp_write(s, len);
}