#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* layer; } ;
typedef  TYPE_2__ wavefront_program ;
struct TYPE_8__ {int* prog_status; int* patch_status; } ;
typedef  TYPE_3__ snd_wavefront_t ;
struct TYPE_6__ {size_t patch_number; scalar_t__ mute; } ;

/* Variables and functions */
 int /*<<< orphan*/  WFC_UPLOAD_PROGRAM ; 
 int WF_MAX_PROGRAM ; 
 int WF_NUM_LAYERS ; 
 int WF_PROGRAM_BYTES ; 
 int WF_SLOT_USED ; 
 int /*<<< orphan*/  demunge_buf (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  snd_printk (char*,int) ; 
 int snd_wavefront_cmd (TYPE_3__*,int /*<<< orphan*/ ,unsigned char*,unsigned char*) ; 

__attribute__((used)) static int
wavefront_get_program_status (snd_wavefront_t *dev)

{
	unsigned char progbuf[WF_PROGRAM_BYTES];
	wavefront_program prog;
	unsigned char prognum;
	int i, x, l, cnt;

	for (i = 0; i < WF_MAX_PROGRAM; i++) {
		prognum = i;

		if ((x = snd_wavefront_cmd (dev, WFC_UPLOAD_PROGRAM, progbuf,
					&prognum)) == 0) {

			dev->prog_status[i] |= WF_SLOT_USED;

			demunge_buf (progbuf, (unsigned char *) &prog,
				     WF_PROGRAM_BYTES);

			for (l = 0; l < WF_NUM_LAYERS; l++) {
				if (prog.layer[l].mute) {
					dev->patch_status
						[prog.layer[l].patch_number] |=
						WF_SLOT_USED;
				}
			}
		} else if (x == 1) { /* Bad program number */
			dev->prog_status[i] = 0;
		} else {
			snd_printk ("upload program "
				    "error 0x%x\n", x);
			dev->prog_status[i] = 0;
		}
	}

	for (i = 0, cnt = 0; i < WF_MAX_PROGRAM; i++) {
		if (dev->prog_status[i]) {
			cnt++;
		}
	}

	snd_printk ("%d programs slots in use\n", cnt);

	return (0);
}