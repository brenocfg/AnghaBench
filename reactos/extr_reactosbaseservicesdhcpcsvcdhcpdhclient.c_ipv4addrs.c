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
struct in_addr {int dummy; } ;

/* Variables and functions */
 scalar_t__ inet_aton (char*,struct in_addr*) ; 
 int /*<<< orphan*/  note (char*,char*) ; 
 char* strtok (char*,char*) ; 

int
ipv4addrs(char * buf)
{
    char *tmp;
    struct in_addr jnk;
    int i = 0;

    note("Input: %s", buf);

    do {
        tmp = strtok(buf, " ");
        note("got %s", tmp);
		if( tmp && inet_aton(tmp, &jnk) ) i++;
        buf = NULL;
    } while( tmp );

    return (i);
}