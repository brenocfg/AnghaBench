#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct snd_pcm_hardware {int formats; } ;
struct TYPE_3__ {int mask; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* CFG_HW_SUPPORTED_FORMATS ; 
 int /*<<< orphan*/  XENSND_LIST_SEPARATOR ; 
 int /*<<< orphan*/  XENSND_SAMPLE_FORMAT_MAX_LEN ; 
 int /*<<< orphan*/  strncasecmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strsep (char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfg_formats(char *list, unsigned int len,
			const char *path, struct snd_pcm_hardware *pcm_hw)
{
	u64 formats;
	char *cur_format;
	int i;

	formats = 0;
	while ((cur_format = strsep(&list, XENSND_LIST_SEPARATOR))) {
		for (i = 0; i < ARRAY_SIZE(CFG_HW_SUPPORTED_FORMATS); i++)
			if (!strncasecmp(cur_format,
					 CFG_HW_SUPPORTED_FORMATS[i].name,
					 XENSND_SAMPLE_FORMAT_MAX_LEN))
				formats |= CFG_HW_SUPPORTED_FORMATS[i].mask;
	}

	if (formats)
		pcm_hw->formats = formats;
}