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
struct hdac_device {int afg_function_id; int afg_unsol; int mfg_function_id; int mfg_unsol; void* mfg; void* afg; } ;
typedef  void* hda_nid_t ;

/* Variables and functions */
#define  AC_GRP_AUDIO_FUNCTION 129 
#define  AC_GRP_MODEM_FUNCTION 128 
 int /*<<< orphan*/  AC_NODE_ROOT ; 
 int /*<<< orphan*/  AC_PAR_FUNCTION_TYPE ; 
 int snd_hdac_get_sub_nodes (struct hdac_device*,int /*<<< orphan*/ ,void**) ; 
 int snd_hdac_read_parm (struct hdac_device*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_fg_nodes(struct hdac_device *codec)
{
	int i, total_nodes, function_id;
	hda_nid_t nid;

	total_nodes = snd_hdac_get_sub_nodes(codec, AC_NODE_ROOT, &nid);
	for (i = 0; i < total_nodes; i++, nid++) {
		function_id = snd_hdac_read_parm(codec, nid,
						 AC_PAR_FUNCTION_TYPE);
		switch (function_id & 0xff) {
		case AC_GRP_AUDIO_FUNCTION:
			codec->afg = nid;
			codec->afg_function_id = function_id & 0xff;
			codec->afg_unsol = (function_id >> 8) & 1;
			break;
		case AC_GRP_MODEM_FUNCTION:
			codec->mfg = nid;
			codec->mfg_function_id = function_id & 0xff;
			codec->mfg_unsol = (function_id >> 8) & 1;
			break;
		default:
			break;
		}
	}
}