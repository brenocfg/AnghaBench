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
typedef  int /*<<< orphan*/  uint8_t ;
struct vt_h264_encoder {int dummy; } ;
struct darray {size_t num; int /*<<< orphan*/  const* array; } ;
typedef  int /*<<< orphan*/  OSStatus ;
typedef  int /*<<< orphan*/  CMFormatDescriptionRef ;

/* Variables and functions */
 int /*<<< orphan*/  CMVideoFormatDescriptionGetH264ParameterSetAtIndex (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  log_osstatus (int /*<<< orphan*/ ,struct vt_h264_encoder*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noErr ; 
 int /*<<< orphan*/  packet_put (struct darray*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  packet_put_startcode (struct darray*,int) ; 

__attribute__((used)) static bool handle_keyframe(struct vt_h264_encoder *enc,
			    CMFormatDescriptionRef format_desc,
			    size_t param_count, struct darray *packet,
			    struct darray *extra_data)
{
	OSStatus code;
	const uint8_t *param;
	size_t param_size;

	for (size_t i = 0; i < param_count; i++) {
		code = CMVideoFormatDescriptionGetH264ParameterSetAtIndex(
			format_desc, i, &param, &param_size, NULL, NULL);
		if (code != noErr) {
			log_osstatus(LOG_ERROR, enc,
				     "getting NAL parameter "
				     "at index",
				     code);
			return false;
		}

		packet_put_startcode(packet, 4);
		packet_put(packet, param, param_size);
	}

	// if we were passed an extra_data array, fill it with
	// SPS, PPS, etc.
	if (extra_data != NULL)
		packet_put(extra_data, packet->array, packet->num);

	return true;
}