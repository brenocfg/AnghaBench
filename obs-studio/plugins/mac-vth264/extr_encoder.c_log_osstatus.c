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
struct vt_h264_encoder {int dummy; } ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/  CFErrorRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFErrorCopyDescription (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFErrorCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT_BLOG (int,char*,char const*,char*) ; 
 int /*<<< orphan*/  VT_LOG (int,char*,char const*,char*) ; 
 int /*<<< orphan*/  bfree (char*) ; 
 char* cfstr_copy_cstr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFErrorDomainOSStatus ; 
 int /*<<< orphan*/  kCFStringEncodingUTF8 ; 

__attribute__((used)) static void log_osstatus(int log_level, struct vt_h264_encoder *enc,
			 const char *context, OSStatus code)
{
	char *c_str = NULL;
	CFErrorRef err = CFErrorCreate(kCFAllocatorDefault,
				       kCFErrorDomainOSStatus, code, NULL);
	CFStringRef str = CFErrorCopyDescription(err);

	c_str = cfstr_copy_cstr(str, kCFStringEncodingUTF8);
	if (c_str) {
		if (enc)
			VT_BLOG(log_level, "Error in %s: %s", context, c_str);
		else
			VT_LOG(log_level, "Error in %s: %s", context, c_str);
	}

	bfree(c_str);
	CFRelease(str);
	CFRelease(err);
}