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
struct cmdif {int dummy; } ;

/* Variables and functions */
 unsigned char DIGITAL_MIXER_IN0 ; 
 unsigned char E2SINK_MAX ; 
 unsigned char LS_MIXER_IN ; 
 unsigned char LS_SRC_DECIMATOR ; 
 unsigned char LS_SRC_DECIMATORM ; 
 unsigned char LS_SRC_INTERPOLATOR ; 
 unsigned char LS_SRC_INTERPOLATORM ; 
 int /*<<< orphan*/  SEND_PSEL (struct cmdif*,unsigned char,unsigned char) ; 
 unsigned char SPLIT_PATH ; 
 unsigned char** lbusin2out ; 
 int /*<<< orphan*/  snd_printdd (char*,unsigned char,unsigned char) ; 

__attribute__((used)) static void
alloclbuspath(struct cmdif *cif, unsigned char source,
	      unsigned char *path, unsigned char *mixer, unsigned char *s)
{
	while (*path != 0xff) {
		unsigned char sink, type;

		sink = *path & (~SPLIT_PATH);
		if (sink != E2SINK_MAX) {
			snd_printdd("alloc path 0x%x->0x%x\n", source, sink);
			SEND_PSEL(cif, source, sink);
			source = lbusin2out[sink][0];
			type = lbusin2out[sink][1];
			if (type == LS_MIXER_IN) {
				if (mixer)
					*mixer = sink - DIGITAL_MIXER_IN0;
			}
			if (type == LS_SRC_DECIMATORM ||
			    type == LS_SRC_DECIMATOR ||
			    type == LS_SRC_INTERPOLATORM ||
			    type == LS_SRC_INTERPOLATOR) {
				if (s) {
					if (s[0] != 0xff)
						s[1] = sink;
					else
						s[0] = sink;
				}
			}
		}
		if (*path++ & SPLIT_PATH) {
			unsigned char *npath = path;

			while (*npath != 0xff)
				npath++;
			alloclbuspath(cif, source + 1, ++npath, mixer, s);
		}
	}
}