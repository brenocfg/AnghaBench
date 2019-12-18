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
struct snd_info_buffer {int dummy; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PAR_PROC_CAP ; 
 unsigned int AC_PCAP_BENIGN ; 
 unsigned int AC_PCAP_NUM_COEF ; 
 unsigned int AC_PCAP_NUM_COEF_SHIFT ; 
 int /*<<< orphan*/  AC_VERB_GET_COEF_INDEX ; 
 int /*<<< orphan*/  AC_VERB_GET_PROC_COEF ; 
 int /*<<< orphan*/  AC_VERB_SET_COEF_INDEX ; 
 int /*<<< orphan*/  can_dump_coef (struct hda_codec*) ; 
 unsigned int param_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static void print_proc_caps(struct snd_info_buffer *buffer,
			    struct hda_codec *codec, hda_nid_t nid)
{
	unsigned int i, ncoeff, oldindex;
	unsigned int proc_caps = param_read(codec, nid, AC_PAR_PROC_CAP);
	ncoeff = (proc_caps & AC_PCAP_NUM_COEF) >> AC_PCAP_NUM_COEF_SHIFT;
	snd_iprintf(buffer, "  Processing caps: benign=%d, ncoeff=%d\n",
		    proc_caps & AC_PCAP_BENIGN, ncoeff);

	if (!can_dump_coef(codec))
		return;

	/* Note: This is racy - another process could run in parallel and change
	   the coef index too. */
	oldindex = snd_hda_codec_read(codec, nid, 0, AC_VERB_GET_COEF_INDEX, 0);
	for (i = 0; i < ncoeff; i++) {
		unsigned int val;
		snd_hda_codec_write(codec, nid, 0, AC_VERB_SET_COEF_INDEX, i);
		val = snd_hda_codec_read(codec, nid, 0, AC_VERB_GET_PROC_COEF,
					 0);
		snd_iprintf(buffer, "    Coeff 0x%02x: 0x%04x\n", i, val);
	}
	snd_hda_codec_write(codec, nid, 0, AC_VERB_SET_COEF_INDEX, oldindex);
}