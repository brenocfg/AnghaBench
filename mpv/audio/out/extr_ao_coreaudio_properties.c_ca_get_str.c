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
typedef  int /*<<< orphan*/  ca_sel ;
typedef  int /*<<< orphan*/  ca_scope ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/  AudioObjectID ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_CA_ERROR_SILENT_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ca_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void**) ; 
 char* cfstr_get_cstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coreaudio_error ; 

OSStatus ca_get_str(AudioObjectID id, ca_scope scope, ca_sel selector,
                    char **data)
{
    CFStringRef string;
    OSStatus err =
        ca_get(id, scope, selector, sizeof(CFStringRef), (void **)&string);
    CHECK_CA_ERROR_SILENT_L(coreaudio_error);

    *data = cfstr_get_cstr(string);
    CFRelease(string);
coreaudio_error:
    return err;
}