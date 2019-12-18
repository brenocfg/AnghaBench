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
typedef  int /*<<< orphan*/  CMSampleBufferRef ;
typedef  scalar_t__ CFDictionaryRef ;
typedef  scalar_t__ CFBooleanRef ;
typedef  int /*<<< orphan*/ * CFArrayRef ;

/* Variables and functions */
 scalar_t__ CFArrayGetValueAtIndex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ CFDictionaryGetValue (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CMSampleBufferGetSampleAttachmentsArray (int /*<<< orphan*/ ,int) ; 
 scalar_t__ kCFBooleanFalse ; 
 int /*<<< orphan*/  kCMSampleAttachmentKey_DependsOnOthers ; 

__attribute__((used)) static bool is_sample_keyframe(CMSampleBufferRef buffer)
{
	CFArrayRef attachments =
		CMSampleBufferGetSampleAttachmentsArray(buffer, false);
	if (attachments != NULL) {
		CFDictionaryRef attachment;
		CFBooleanRef has_dependencies;
		attachment =
			(CFDictionaryRef)CFArrayGetValueAtIndex(attachments, 0);
		has_dependencies = (CFBooleanRef)CFDictionaryGetValue(
			attachment, kCMSampleAttachmentKey_DependsOnOthers);
		return has_dependencies == kCFBooleanFalse;
	}

	return false;
}