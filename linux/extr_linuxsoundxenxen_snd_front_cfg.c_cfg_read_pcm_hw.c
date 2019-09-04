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
struct snd_pcm_hardware {int channels_min; int channels_max; size_t buffer_bytes_max; scalar_t__ rate_min; scalar_t__ rate_max; size_t period_bytes_max; int periods_max; int period_bytes_min; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (char*) ; 
 struct snd_pcm_hardware SND_DRV_PCM_HW_DEFAULT ; 
 int /*<<< orphan*/  XBT_NIL ; 
 int /*<<< orphan*/  XENSND_FIELD_BUFFER_SIZE ; 
 int /*<<< orphan*/  XENSND_FIELD_CHANNELS_MAX ; 
 int /*<<< orphan*/  XENSND_FIELD_CHANNELS_MIN ; 
 int /*<<< orphan*/  XENSND_FIELD_SAMPLE_FORMATS ; 
 int /*<<< orphan*/  XENSND_FIELD_SAMPLE_RATES ; 
 int /*<<< orphan*/  cfg_formats (char*,unsigned int,char const*,struct snd_pcm_hardware*) ; 
 int /*<<< orphan*/  cfg_hw_rates (char*,unsigned int,char const*,struct snd_pcm_hardware*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* xenbus_read (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,unsigned int*) ; 
 void* xenbus_read_unsigned (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfg_read_pcm_hw(const char *path,
			    struct snd_pcm_hardware *parent_pcm_hw,
			    struct snd_pcm_hardware *pcm_hw)
{
	char *list;
	int val;
	size_t buf_sz;
	unsigned int len;

	/* Inherit parent's PCM HW and read overrides from XenStore. */
	if (parent_pcm_hw)
		*pcm_hw = *parent_pcm_hw;
	else
		*pcm_hw = SND_DRV_PCM_HW_DEFAULT;

	val = xenbus_read_unsigned(path, XENSND_FIELD_CHANNELS_MIN, 0);
	if (val)
		pcm_hw->channels_min = val;

	val = xenbus_read_unsigned(path, XENSND_FIELD_CHANNELS_MAX, 0);
	if (val)
		pcm_hw->channels_max = val;

	list = xenbus_read(XBT_NIL, path, XENSND_FIELD_SAMPLE_RATES, &len);
	if (!IS_ERR(list)) {
		cfg_hw_rates(list, len, path, pcm_hw);
		kfree(list);
	}

	list = xenbus_read(XBT_NIL, path, XENSND_FIELD_SAMPLE_FORMATS, &len);
	if (!IS_ERR(list)) {
		cfg_formats(list, len, path, pcm_hw);
		kfree(list);
	}

	buf_sz = xenbus_read_unsigned(path, XENSND_FIELD_BUFFER_SIZE, 0);
	if (buf_sz)
		pcm_hw->buffer_bytes_max = buf_sz;

	/* Update configuration to match new values. */
	if (pcm_hw->channels_min > pcm_hw->channels_max)
		pcm_hw->channels_min = pcm_hw->channels_max;

	if (pcm_hw->rate_min > pcm_hw->rate_max)
		pcm_hw->rate_min = pcm_hw->rate_max;

	pcm_hw->period_bytes_max = pcm_hw->buffer_bytes_max;

	pcm_hw->periods_max = pcm_hw->period_bytes_max /
		pcm_hw->period_bytes_min;
}