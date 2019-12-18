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
struct vt_h264_encoder {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  vt_pix_fmt; } ;
typedef  int /*<<< orphan*/  CFNumberRef ;
typedef  int /*<<< orphan*/  CFMutableDictionaryRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFDictionaryAddValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFDictionaryCreateMutable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFNumberCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFNumberSInt32Type ; 
 int /*<<< orphan*/  kCFTypeDictionaryKeyCallBacks ; 
 int /*<<< orphan*/  kCFTypeDictionaryValueCallBacks ; 
 int /*<<< orphan*/  kCVPixelBufferHeightKey ; 
 int /*<<< orphan*/  kCVPixelBufferPixelFormatTypeKey ; 
 int /*<<< orphan*/  kCVPixelBufferWidthKey ; 

__attribute__((used)) static inline CFMutableDictionaryRef
create_pixbuf_spec(struct vt_h264_encoder *enc)
{
	CFMutableDictionaryRef pixbuf_spec = CFDictionaryCreateMutable(
		kCFAllocatorDefault, 3, &kCFTypeDictionaryKeyCallBacks,
		&kCFTypeDictionaryValueCallBacks);

	CFNumberRef n =
		CFNumberCreate(NULL, kCFNumberSInt32Type, &enc->vt_pix_fmt);
	CFDictionaryAddValue(pixbuf_spec, kCVPixelBufferPixelFormatTypeKey, n);
	CFRelease(n);

	n = CFNumberCreate(NULL, kCFNumberSInt32Type, &enc->width);
	CFDictionaryAddValue(pixbuf_spec, kCVPixelBufferWidthKey, n);
	CFRelease(n);

	n = CFNumberCreate(NULL, kCFNumberSInt32Type, &enc->height);
	CFDictionaryAddValue(pixbuf_spec, kCVPixelBufferHeightKey, n);
	CFRelease(n);

	return pixbuf_spec;
}