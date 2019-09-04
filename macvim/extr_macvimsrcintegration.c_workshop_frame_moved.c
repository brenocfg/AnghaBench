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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  NOCATGETS (char*) ; 
 int /*<<< orphan*/  dummy ; 
 scalar_t__ sd ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  vim_snprintf (char*,int,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  write (scalar_t__,char*,int /*<<< orphan*/ ) ; 

void workshop_frame_moved(int new_x, int new_y, int new_w, int new_h)
{
	char buffer[200];

	if (sd >= 0)
	{
		vim_snprintf(buffer, sizeof(buffer),
				NOCATGETS("frameAt %d %d %d %d\n"),
				new_x, new_y, new_w, new_h);
		dummy = write(sd, buffer, strlen(buffer));
	}
}