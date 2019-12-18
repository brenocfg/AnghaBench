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
typedef  float int32_t ;
typedef  int /*<<< orphan*/  VTCompressionSessionRef ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  int /*<<< orphan*/  CFNumberRef ;
typedef  int /*<<< orphan*/  CFMutableArrayRef ;

/* Variables and functions */
 int /*<<< orphan*/  CFArrayAppendValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFArrayCreateMutable (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CFNumberCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  SESSION_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kCFAllocatorDefault ; 
 int /*<<< orphan*/  kCFNumberFloatType ; 
 int /*<<< orphan*/  kCFNumberIntType ; 
 int /*<<< orphan*/  kCFTypeArrayCallBacks ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_AverageBitRate ; 
 int /*<<< orphan*/  kVTCompressionPropertyKey_DataRateLimits ; 
 int /*<<< orphan*/  kVTPropertyNotSupportedErr ; 
 int /*<<< orphan*/  log_osstatus (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noErr ; 
 int /*<<< orphan*/  session_set_prop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_set_prop_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static OSStatus session_set_bitrate(VTCompressionSessionRef session,
				    int new_bitrate, bool limit_bitrate,
				    int max_bitrate, float max_bitrate_window)
{
	OSStatus code;

	SESSION_CHECK(session_set_prop_int(
		session, kVTCompressionPropertyKey_AverageBitRate,
		new_bitrate * 1000));

	if (limit_bitrate) {
		int32_t cpb_size = max_bitrate * 125 * max_bitrate_window;

		CFNumberRef cf_cpb_size =
			CFNumberCreate(NULL, kCFNumberIntType, &cpb_size);
		CFNumberRef cf_cpb_window_s = CFNumberCreate(
			NULL, kCFNumberFloatType, &max_bitrate_window);

		CFMutableArrayRef rate_control = CFArrayCreateMutable(
			kCFAllocatorDefault, 2, &kCFTypeArrayCallBacks);

		CFArrayAppendValue(rate_control, cf_cpb_size);
		CFArrayAppendValue(rate_control, cf_cpb_window_s);

		code = session_set_prop(
			session, kVTCompressionPropertyKey_DataRateLimits,
			rate_control);

		CFRelease(cf_cpb_size);
		CFRelease(cf_cpb_window_s);
		CFRelease(rate_control);

		if (code == kVTPropertyNotSupportedErr) {
			log_osstatus(LOG_WARNING, NULL,
				     "setting DataRateLimits on session", code);
			return noErr;
		}
	}

	return noErr;
}