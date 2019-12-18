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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum audio_format { ____Placeholder_audio_format } audio_format ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_CONV (char*,char*,int) ; 
 int AUDIO_FORMAT_16BIT ; 
 int AUDIO_FORMAT_32BIT ; 
 int AUDIO_FORMAT_FLOAT ; 
 int /*<<< orphan*/  AUDIO_TEST (char*,int) ; 

__attribute__((used)) static enum audio_format convert_vlc_audio_format(char *format)
{
#define AUDIO_TEST(val, ret)        \
	if (chroma_is(format, val)) \
	return ret
#define AUDIO_CONV(val, new_val, ret)                               \
	do {                                                        \
		if (chroma_is(format, val)) {                       \
			*(uint32_t *)format = *(uint32_t *)new_val; \
			return ret;                                 \
		}                                                   \
	} while (false)

	AUDIO_TEST("S16N", AUDIO_FORMAT_16BIT);
	AUDIO_TEST("S32N", AUDIO_FORMAT_32BIT);
	AUDIO_TEST("FL32", AUDIO_FORMAT_FLOAT);

	AUDIO_CONV("U16N", "S16N", AUDIO_FORMAT_16BIT);
	AUDIO_CONV("U32N", "S32N", AUDIO_FORMAT_32BIT);
	AUDIO_CONV("S24N", "S32N", AUDIO_FORMAT_32BIT);
	AUDIO_CONV("U24N", "S32N", AUDIO_FORMAT_32BIT);
	AUDIO_CONV("FL64", "FL32", AUDIO_FORMAT_FLOAT);

	AUDIO_CONV("S16I", "S16N", AUDIO_FORMAT_16BIT);
	AUDIO_CONV("U16I", "S16N", AUDIO_FORMAT_16BIT);
	AUDIO_CONV("S24I", "S32N", AUDIO_FORMAT_32BIT);
	AUDIO_CONV("U24I", "S32N", AUDIO_FORMAT_32BIT);
	AUDIO_CONV("S32I", "S32N", AUDIO_FORMAT_32BIT);
	AUDIO_CONV("U32I", "S32N", AUDIO_FORMAT_32BIT);
#undef AUDIO_CONV
#undef AUDIO_TEST

	*(uint32_t *)format = *(uint32_t *)"FL32";
	return AUDIO_FORMAT_FLOAT;
}