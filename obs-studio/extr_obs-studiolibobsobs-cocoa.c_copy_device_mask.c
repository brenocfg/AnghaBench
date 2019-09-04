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
typedef  int /*<<< orphan*/  UInt32 ;
typedef  int /*<<< orphan*/  CFNumberRef ;
typedef  int /*<<< orphan*/  CFMutableDictionaryRef ;
typedef  int /*<<< orphan*/  CFDictionaryRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFDictionaryCreateMutable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFDictionarySetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFNumberCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFNumberIntType ; 
 int /*<<< orphan*/  kCFTypeDictionaryKeyCallBacks ; 
 int /*<<< orphan*/  kCFTypeDictionaryValueCallBacks ; 
 int /*<<< orphan*/  kIOHIDDeviceUsageKey ; 
 int /*<<< orphan*/  kIOHIDDeviceUsagePageKey ; 

__attribute__((used)) static inline CFDictionaryRef copy_device_mask(UInt32 page, UInt32 usage)
{
	CFMutableDictionaryRef dict = CFDictionaryCreateMutable(
			kCFAllocatorDefault, 2,
			&kCFTypeDictionaryKeyCallBacks,
			&kCFTypeDictionaryValueCallBacks);

	CFNumberRef value;
	// Add the page value.
	value = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &page);
	CFDictionarySetValue(dict, CFSTR(kIOHIDDeviceUsagePageKey), value);
	CFRelease(value);

	// Add the usage value (which is only valid if page value exists).
	value = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &usage);
	CFDictionarySetValue(dict, CFSTR(kIOHIDDeviceUsageKey), value);
	CFRelease(value);

	return dict;
}