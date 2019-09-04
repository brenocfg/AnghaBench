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
struct yam_mcs {int bitrate; unsigned char* bits; struct yam_mcs* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  YAM_1200 ; 
 int /*<<< orphan*/  YAM_9600 ; 
 unsigned char* add_mcs (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct yam_mcs* yam_data ; 

__attribute__((used)) static unsigned char *get_mcs(int bitrate)
{
	struct yam_mcs *p;

	p = yam_data;
	while (p) {
		if (p->bitrate == bitrate)
			return p->bits;
		p = p->next;
	}

	/* Load predefined mcs data */
	switch (bitrate) {
	case 1200:
		/* setting predef as YAM_1200 for loading predef 1200 mcs */
		return add_mcs(NULL, bitrate, YAM_1200);
	default:
		/* setting predef as YAM_9600 for loading predef 9600 mcs */
		return add_mcs(NULL, bitrate, YAM_9600);
	}
}