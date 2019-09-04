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
 size_t MAXERRLEN ; 
 int /*<<< orphan*/  syslog (int,char*,int,char const*) ; 

__attribute__((used)) static int print_syslog(const char *str, size_t len, void *levPtr)
{
    int level = *(int *)levPtr;
    int ilen = (len > MAXERRLEN) ? MAXERRLEN : len;

    syslog(level, "%.*s", ilen, str);

    return ilen;
}