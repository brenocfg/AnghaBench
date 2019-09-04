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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int strlen (char*) ; 
 int /*<<< orphan*/  vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void strcat_vprintf(char *buf, int buf_size, const char *fmt, va_list ap)
{
	int len;
	len = strlen (buf);
	vsnprintf (buf + len, buf_size - len, fmt, ap);
}