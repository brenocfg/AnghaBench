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
 int /*<<< orphan*/  SetCurrentDirectory (char*) ; 

int _chdrive(int drive)
{
    char temp [3] = "-:";
    temp[0] = drive + 'A' - 1;
    return !SetCurrentDirectory(temp);
}