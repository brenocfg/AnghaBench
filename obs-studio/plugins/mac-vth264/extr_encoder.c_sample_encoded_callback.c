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
typedef  int /*<<< orphan*/  VTEncodeInfoFlags ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  void* CVPixelBufferRef ;
typedef  void* CMSimpleQueueRef ;
typedef  int /*<<< orphan*/ * CMSampleBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (void*) ; 
 int /*<<< orphan*/  CFRetain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CMSimpleQueueEnqueue (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ ) ; 

void sample_encoded_callback(void *data, void *source, OSStatus status,
			     VTEncodeInfoFlags info_flags,
			     CMSampleBufferRef buffer)
{
	UNUSED_PARAMETER(status);
	UNUSED_PARAMETER(info_flags);

	CMSimpleQueueRef queue = data;
	CVPixelBufferRef pixbuf = source;
	if (buffer != NULL) {
		CFRetain(buffer);
		CMSimpleQueueEnqueue(queue, buffer);
	}
	CFRelease(pixbuf);
}