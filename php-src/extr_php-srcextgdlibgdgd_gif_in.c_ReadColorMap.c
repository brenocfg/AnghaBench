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
typedef  int /*<<< orphan*/  rgb ;
typedef  int /*<<< orphan*/  gdIOCtx ;

/* Variables and functions */
 size_t CM_BLUE ; 
 size_t CM_GREEN ; 
 size_t CM_RED ; 
 int FALSE ; 
 int /*<<< orphan*/  ReadOK (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int TRUE ; 

__attribute__((used)) static int ReadColorMap(gdIOCtx *fd, int number, unsigned char (*buffer)[256]) /* {{{ */
{
	int             i;
	unsigned char   rgb[3];


	for (i = 0; i < number; ++i) {
		if (! ReadOK(fd, rgb, sizeof(rgb))) {
			return TRUE;
		}
		buffer[CM_RED][i] = rgb[0] ;
		buffer[CM_GREEN][i] = rgb[1] ;
		buffer[CM_BLUE][i] = rgb[2] ;
	}


	return FALSE;
}