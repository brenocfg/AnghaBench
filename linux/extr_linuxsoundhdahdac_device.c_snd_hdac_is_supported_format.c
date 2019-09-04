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
struct hdac_device {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;
struct TYPE_2__ {unsigned int hda_fmt; } ;

/* Variables and functions */
 int AC_PAR_PCM_RATE_BITS ; 
 unsigned int AC_SUPFMT_PCM ; 
 unsigned int AC_SUPPCM_BITS_16 ; 
 unsigned int AC_SUPPCM_BITS_20 ; 
 unsigned int AC_SUPPCM_BITS_24 ; 
 unsigned int AC_SUPPCM_BITS_32 ; 
 unsigned int AC_SUPPCM_BITS_8 ; 
 unsigned int query_pcm_param (struct hdac_device*,int /*<<< orphan*/ ) ; 
 unsigned int query_stream_param (struct hdac_device*,int /*<<< orphan*/ ) ; 
 TYPE_1__* rate_bits ; 

bool snd_hdac_is_supported_format(struct hdac_device *codec, hda_nid_t nid,
				  unsigned int format)
{
	int i;
	unsigned int val = 0, rate, stream;

	val = query_pcm_param(codec, nid);
	if (!val)
		return false;

	rate = format & 0xff00;
	for (i = 0; i < AC_PAR_PCM_RATE_BITS; i++)
		if (rate_bits[i].hda_fmt == rate) {
			if (val & (1 << i))
				break;
			return false;
		}
	if (i >= AC_PAR_PCM_RATE_BITS)
		return false;

	stream = query_stream_param(codec, nid);
	if (!stream)
		return false;

	if (stream & AC_SUPFMT_PCM) {
		switch (format & 0xf0) {
		case 0x00:
			if (!(val & AC_SUPPCM_BITS_8))
				return false;
			break;
		case 0x10:
			if (!(val & AC_SUPPCM_BITS_16))
				return false;
			break;
		case 0x20:
			if (!(val & AC_SUPPCM_BITS_20))
				return false;
			break;
		case 0x30:
			if (!(val & AC_SUPPCM_BITS_24))
				return false;
			break;
		case 0x40:
			if (!(val & AC_SUPPCM_BITS_32))
				return false;
			break;
		default:
			return false;
		}
	} else {
		/* FIXME: check for float32 and AC3? */
	}

	return true;
}