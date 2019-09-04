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
struct vt_h264_encoder {int /*<<< orphan*/  extra_data; int /*<<< orphan*/  packet_data; int /*<<< orphan*/ * session; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VTCompressionSessionInvalidate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfree (struct vt_h264_encoder*) ; 
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vt_h264_destroy(void *data)
{
	struct vt_h264_encoder *enc = data;

	if (enc) {
		if (enc->session != NULL) {
			VTCompressionSessionInvalidate(enc->session);
			CFRelease(enc->session);
		}
		da_free(enc->packet_data);
		da_free(enc->extra_data);
		bfree(enc);
	}
}