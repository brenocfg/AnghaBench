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
typedef  int Boolean ;

/* Variables and functions */
 int TEMP_BUF_SIZE ; 
 int /*<<< orphan*/  get_part (char*,int,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static Boolean
proportional(char *font)
{
    char buf[TEMP_BUF_SIZE];

    get_part(font, 11, buf);

    return !strcmp(buf, "p") || !strcmp(buf, "P");
}