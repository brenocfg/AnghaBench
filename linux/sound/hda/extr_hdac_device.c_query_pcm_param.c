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
struct hdac_device {scalar_t__ afg; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_PAR_PCM ; 
 int AC_WCAP_FORMAT_OVRD ; 
 int get_wcaps (struct hdac_device*,scalar_t__) ; 
 unsigned int snd_hdac_read_parm (struct hdac_device*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int query_pcm_param(struct hdac_device *codec, hda_nid_t nid)
{
	unsigned int val = 0;

	if (nid != codec->afg &&
	    (get_wcaps(codec, nid) & AC_WCAP_FORMAT_OVRD))
		val = snd_hdac_read_parm(codec, nid, AC_PAR_PCM);
	if (!val || val == -1)
		val = snd_hdac_read_parm(codec, codec->afg, AC_PAR_PCM);
	if (!val || val == -1)
		return 0;
	return val;
}