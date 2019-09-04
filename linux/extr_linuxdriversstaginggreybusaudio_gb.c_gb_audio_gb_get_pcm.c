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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct gb_connection {int dummy; } ;
struct gb_audio_get_pcm_response {int /*<<< orphan*/  sig_bits; int /*<<< orphan*/  channels; int /*<<< orphan*/  rate; int /*<<< orphan*/  format; } ;
struct gb_audio_get_pcm_request {int /*<<< orphan*/  data_cport; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  GB_AUDIO_TYPE_GET_PCM ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int gb_operation_sync (struct gb_connection*,int /*<<< orphan*/ ,struct gb_audio_get_pcm_request*,int,struct gb_audio_get_pcm_response*,int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

int gb_audio_gb_get_pcm(struct gb_connection *connection, u16 data_cport,
			u32 *format, u32 *rate, u8 *channels,
			u8 *sig_bits)
{
	struct gb_audio_get_pcm_request req;
	struct gb_audio_get_pcm_response resp;
	int ret;

	req.data_cport = cpu_to_le16(data_cport);

	ret = gb_operation_sync(connection, GB_AUDIO_TYPE_GET_PCM,
				&req, sizeof(req), &resp, sizeof(resp));
	if (ret)
		return ret;

	*format = le32_to_cpu(resp.format);
	*rate = le32_to_cpu(resp.rate);
	*channels = resp.channels;
	*sig_bits = resp.sig_bits;

	return 0;
}