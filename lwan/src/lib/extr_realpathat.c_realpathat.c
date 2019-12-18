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
struct stat {int dummy; } ;

/* Variables and functions */
 char* realpathat2 (int,char*,char const*,char*,struct stat*) ; 

char *
realpathat(int dirfd, char *dirfdpath, const char *name, char *resolved)
{
    struct stat st;
    return realpathat2(dirfd, dirfdpath, name, resolved, &st);
}