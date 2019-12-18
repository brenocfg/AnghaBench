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
typedef  int /*<<< orphan*/  CFStringRef ;
typedef  int /*<<< orphan*/  CFMutableDictionaryRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFDictionaryAddValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFDictionaryCreateMutable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFStringCreateWithFileSystemRepresentation (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ENABLE_HW_ACCEL ; 
 int /*<<< orphan*/  ENCODER_ID ; 
 int /*<<< orphan*/  REQUIRE_HW_ACCEL ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFBooleanFalse ; 
 int /*<<< orphan*/  kCFBooleanTrue ; 
 int /*<<< orphan*/  kCFTypeDictionaryKeyCallBacks ; 
 int /*<<< orphan*/  kCFTypeDictionaryValueCallBacks ; 

__attribute__((used)) static inline CFMutableDictionaryRef
create_encoder_spec(const char *vt_encoder_id)
{
	CFMutableDictionaryRef encoder_spec = CFDictionaryCreateMutable(
		kCFAllocatorDefault, 3, &kCFTypeDictionaryKeyCallBacks,
		&kCFTypeDictionaryValueCallBacks);

	CFStringRef id =
		CFStringCreateWithFileSystemRepresentation(NULL, vt_encoder_id);
	CFDictionaryAddValue(encoder_spec, ENCODER_ID, id);
	CFRelease(id);

	CFDictionaryAddValue(encoder_spec, ENABLE_HW_ACCEL, kCFBooleanTrue);
	CFDictionaryAddValue(encoder_spec, REQUIRE_HW_ACCEL, kCFBooleanFalse);

	return encoder_spec;
}