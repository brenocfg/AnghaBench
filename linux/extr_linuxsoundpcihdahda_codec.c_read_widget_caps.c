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
struct TYPE_2__ {int num_nodes; int /*<<< orphan*/  start_nid; } ;
struct hda_codec {TYPE_1__ core; int /*<<< orphan*/ * wcaps; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PAR_AUDIO_WIDGET_CAP ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/ * kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hdac_read_parm_uncached (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_widget_caps(struct hda_codec *codec, hda_nid_t fg_node)
{
	int i;
	hda_nid_t nid;

	codec->wcaps = kmalloc_array(codec->core.num_nodes, 4, GFP_KERNEL);
	if (!codec->wcaps)
		return -ENOMEM;
	nid = codec->core.start_nid;
	for (i = 0; i < codec->core.num_nodes; i++, nid++)
		codec->wcaps[i] = snd_hdac_read_parm_uncached(&codec->core,
					nid, AC_PAR_AUDIO_WIDGET_CAP);
	return 0;
}