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
union cmdret {int* retwords; } ;
typedef  int u32 ;
struct cmdif {int dummy; } ;

/* Variables and functions */
 union cmdret CMDRET_ZERO ; 
 int EIO ; 
 int MAX_WRITE_RETRY ; 
 int /*<<< orphan*/  SEND_RSRC (struct cmdif*,unsigned char,union cmdret*) ; 
 int /*<<< orphan*/  SEND_SSRC (struct cmdif*,unsigned char,int,int,int) ; 
 int /*<<< orphan*/  snd_printdd (char*,unsigned char,unsigned int,...) ; 

__attribute__((used)) static int
setsamplerate(struct cmdif *cif, unsigned char *intdec, unsigned int rate)
{
	u32 D, M, N;
	union cmdret rptr = CMDRET_ZERO;
	int i;

	snd_printdd("setsamplerate intdec: %d,%d rate: %d\n", intdec[0],
		    intdec[1], rate);
	D = 48000;
	M = ((rate == 48000) ? 47999 : rate) * 65536;
	N = M % D;
	M /= D;
	for (i = 0; i < 2; i++) {
		if (*intdec != 0xff) {
			do {
				SEND_SSRC(cif, *intdec, D, M, N);
				SEND_RSRC(cif, *intdec, &rptr);
			} while (rptr.retwords[1] != D &&
				 rptr.retwords[2] != M &&
				 rptr.retwords[3] != N &&
				 i++ < MAX_WRITE_RETRY);
			if (i > MAX_WRITE_RETRY) {
				snd_printdd("sent samplerate %d: %d failed\n",
					    *intdec, rate);
				return -EIO;
			}
		}
		intdec++;
	}
	return 0;
}