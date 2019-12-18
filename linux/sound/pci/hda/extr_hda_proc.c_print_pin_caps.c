#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_info_buffer {int dummy; } ;
struct TYPE_2__ {int vendor_id; } ;
struct hda_codec {TYPE_1__ core; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_DEFCFG_ASSOC_SHIFT ; 
 unsigned int AC_DEFCFG_DEF_ASSOC ; 
 unsigned int AC_DEFCFG_MISC ; 
 unsigned int AC_DEFCFG_MISC_NO_PRESENCE ; 
 unsigned int AC_DEFCFG_MISC_SHIFT ; 
 unsigned int AC_DEFCFG_PORT_CONN ; 
 unsigned int AC_DEFCFG_PORT_CONN_SHIFT ; 
 unsigned int AC_DEFCFG_SEQUENCE ; 
 unsigned int AC_EAPDBTL_BALANCED ; 
 unsigned int AC_EAPDBTL_EAPD ; 
 unsigned int AC_EAPDBTL_LR_SWAP ; 
 int /*<<< orphan*/  AC_PAR_PIN_CAP ; 
 unsigned int AC_PINCAP_BALANCE ; 
 unsigned int AC_PINCAP_DP ; 
 unsigned int AC_PINCAP_EAPD ; 
 unsigned int AC_PINCAP_HBR ; 
 unsigned int AC_PINCAP_HDMI ; 
 unsigned int AC_PINCAP_HP_DRV ; 
 unsigned int AC_PINCAP_IMP_SENSE ; 
 unsigned int AC_PINCAP_IN ; 
 unsigned int AC_PINCAP_OUT ; 
 unsigned int AC_PINCAP_PRES_DETECT ; 
 unsigned int AC_PINCAP_TRIG_REQ ; 
 unsigned int AC_PINCAP_VREF ; 
 unsigned int AC_PINCAP_VREF_100 ; 
 unsigned int AC_PINCAP_VREF_50 ; 
 unsigned int AC_PINCAP_VREF_80 ; 
 unsigned int AC_PINCAP_VREF_GRD ; 
 unsigned int AC_PINCAP_VREF_HIZ ; 
 unsigned int AC_PINCAP_VREF_SHIFT ; 
 int /*<<< orphan*/  AC_VERB_GET_CONFIG_DEFAULT ; 
 int /*<<< orphan*/  AC_VERB_GET_EAPD_BTLENABLE ; 
 int /*<<< orphan*/  get_jack_color (unsigned int) ; 
 int /*<<< orphan*/  get_jack_connection (unsigned int) ; 
 int /*<<< orphan*/  get_jack_connectivity (unsigned int) ; 
 int /*<<< orphan*/  get_jack_location (unsigned int) ; 
 int /*<<< orphan*/  get_jack_type (unsigned int) ; 
 unsigned int param_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void print_pin_caps(struct snd_info_buffer *buffer,
			   struct hda_codec *codec, hda_nid_t nid,
			   int *supports_vref)
{
	static const char * const jack_conns[4] = {
		"Jack", "N/A", "Fixed", "Both"
	};
	unsigned int caps, val;

	caps = param_read(codec, nid, AC_PAR_PIN_CAP);
	snd_iprintf(buffer, "  Pincap 0x%08x:", caps);
	if (caps & AC_PINCAP_IN)
		snd_iprintf(buffer, " IN");
	if (caps & AC_PINCAP_OUT)
		snd_iprintf(buffer, " OUT");
	if (caps & AC_PINCAP_HP_DRV)
		snd_iprintf(buffer, " HP");
	if (caps & AC_PINCAP_EAPD)
		snd_iprintf(buffer, " EAPD");
	if (caps & AC_PINCAP_PRES_DETECT)
		snd_iprintf(buffer, " Detect");
	if (caps & AC_PINCAP_BALANCE)
		snd_iprintf(buffer, " Balanced");
	if (caps & AC_PINCAP_HDMI) {
		/* Realtek uses this bit as a different meaning */
		if ((codec->core.vendor_id >> 16) == 0x10ec)
			snd_iprintf(buffer, " R/L");
		else {
			if (caps & AC_PINCAP_HBR)
				snd_iprintf(buffer, " HBR");
			snd_iprintf(buffer, " HDMI");
		}
	}
	if (caps & AC_PINCAP_DP)
		snd_iprintf(buffer, " DP");
	if (caps & AC_PINCAP_TRIG_REQ)
		snd_iprintf(buffer, " Trigger");
	if (caps & AC_PINCAP_IMP_SENSE)
		snd_iprintf(buffer, " ImpSense");
	snd_iprintf(buffer, "\n");
	if (caps & AC_PINCAP_VREF) {
		unsigned int vref =
			(caps & AC_PINCAP_VREF) >> AC_PINCAP_VREF_SHIFT;
		snd_iprintf(buffer, "    Vref caps:");
		if (vref & AC_PINCAP_VREF_HIZ)
			snd_iprintf(buffer, " HIZ");
		if (vref & AC_PINCAP_VREF_50)
			snd_iprintf(buffer, " 50");
		if (vref & AC_PINCAP_VREF_GRD)
			snd_iprintf(buffer, " GRD");
		if (vref & AC_PINCAP_VREF_80)
			snd_iprintf(buffer, " 80");
		if (vref & AC_PINCAP_VREF_100)
			snd_iprintf(buffer, " 100");
		snd_iprintf(buffer, "\n");
		*supports_vref = 1;
	} else
		*supports_vref = 0;
	if (caps & AC_PINCAP_EAPD) {
		val = snd_hda_codec_read(codec, nid, 0,
					 AC_VERB_GET_EAPD_BTLENABLE, 0);
		snd_iprintf(buffer, "  EAPD 0x%x:", val);
		if (val & AC_EAPDBTL_BALANCED)
			snd_iprintf(buffer, " BALANCED");
		if (val & AC_EAPDBTL_EAPD)
			snd_iprintf(buffer, " EAPD");
		if (val & AC_EAPDBTL_LR_SWAP)
			snd_iprintf(buffer, " R/L");
		snd_iprintf(buffer, "\n");
	}
	caps = snd_hda_codec_read(codec, nid, 0, AC_VERB_GET_CONFIG_DEFAULT, 0);
	snd_iprintf(buffer, "  Pin Default 0x%08x: [%s] %s at %s %s\n", caps,
		    jack_conns[(caps & AC_DEFCFG_PORT_CONN) >> AC_DEFCFG_PORT_CONN_SHIFT],
		    get_jack_type(caps),
		    get_jack_connectivity(caps),
		    get_jack_location(caps));
	snd_iprintf(buffer, "    Conn = %s, Color = %s\n",
		    get_jack_connection(caps),
		    get_jack_color(caps));
	/* Default association and sequence values refer to default grouping
	 * of pin complexes and their sequence within the group. This is used
	 * for priority and resource allocation.
	 */
	snd_iprintf(buffer, "    DefAssociation = 0x%x, Sequence = 0x%x\n",
		    (caps & AC_DEFCFG_DEF_ASSOC) >> AC_DEFCFG_ASSOC_SHIFT,
		    caps & AC_DEFCFG_SEQUENCE);
	if (((caps & AC_DEFCFG_MISC) >> AC_DEFCFG_MISC_SHIFT) &
	    AC_DEFCFG_MISC_NO_PRESENCE) {
		/* Miscellaneous bit indicates external hardware does not
		 * support presence detection even if the pin complex
		 * indicates it is supported.
		 */
		snd_iprintf(buffer, "    Misc = NO_PRESENCE\n");
	}
}