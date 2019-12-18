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
typedef  enum af_format { ____Placeholder_af_format } af_format ;
typedef  int /*<<< orphan*/  ALchar ;

/* Variables and functions */
#define  AF_FORMAT_FLOAT 131 
#define  AF_FORMAT_S16 130 
#define  AF_FORMAT_S32 129 
#define  AF_FORMAT_U8 128 
 int AL_FALSE ; 
 int /*<<< orphan*/  AL_RENDERER ; 
 int /*<<< orphan*/  AL_TRUE ; 
 int /*<<< orphan*/  alGetEnumValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alGetString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alIsExtensionPresent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static enum af_format get_supported_format(int format)
{
    switch (format) {
    case AF_FORMAT_U8:
        if (alGetEnumValue((ALchar*)"AL_FORMAT_MONO8"))
            return AF_FORMAT_U8;
        break;

    case AF_FORMAT_S16:
        if (alGetEnumValue((ALchar*)"AL_FORMAT_MONO16"))
            return AF_FORMAT_S16;
        break;

    case AF_FORMAT_S32:
        if (strstr(alGetString(AL_RENDERER), "X-Fi") != NULL)
            return AF_FORMAT_S32;
        break;

    case AF_FORMAT_FLOAT:
        if (alIsExtensionPresent((ALchar*)"AL_EXT_float32") == AL_TRUE)
            return AF_FORMAT_FLOAT;
        break;
    }
    return AL_FALSE;
}