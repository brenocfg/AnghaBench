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
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ trace_write (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int trace_puts(BIO *channel, const char *str)
{
    size_t written;

    if (trace_write(channel, str, strlen(str), &written))
        return (int)written;

    return EOF;
}