#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {int dummy; } ;
struct TYPE_15__ {int array; } ;
struct TYPE_14__ {int addrLen; int /*<<< orphan*/  addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  tcUrl; int /*<<< orphan*/  swfUrl; int /*<<< orphan*/  flashVer; int /*<<< orphan*/  pubPasswd; int /*<<< orphan*/  pubUser; } ;
struct TYPE_16__ {int m_outChunkSize; int m_bSendChunkSizeInfo; int m_bUseNagle; TYPE_3__ m_bindIP; TYPE_1__ Link; } ;
struct TYPE_13__ {char const* array; } ;
struct rtmp_stream {TYPE_4__ path; TYPE_6__ rtmp; int /*<<< orphan*/  output; TYPE_2__ key; TYPE_4__ bind_ip; int /*<<< orphan*/  encoder_name; int /*<<< orphan*/  password; int /*<<< orphan*/  username; } ;
typedef  int /*<<< orphan*/  obs_encoder_t ;

/* Variables and functions */
 int OBS_OUTPUT_BAD_PATH ; 
 int OBS_OUTPUT_CONNECT_FAILED ; 
 int OBS_OUTPUT_INVALID_STREAM ; 
 int /*<<< orphan*/  RTMP_AddStream (TYPE_6__*,char const*) ; 
 int /*<<< orphan*/  RTMP_Connect (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RTMP_ConnectStream (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTMP_EnableWrite (TYPE_6__*) ; 
 int /*<<< orphan*/  RTMP_Init (TYPE_6__*) ; 
 int /*<<< orphan*/  RTMP_SetupURL (TYPE_6__*,int) ; 
 scalar_t__ dstr_cmp (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dstr_copy (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dstr_is_empty (TYPE_4__*) ; 
 int /*<<< orphan*/  info (char*,int) ; 
 int init_send (struct rtmp_stream*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int netif_str_to_addr (int /*<<< orphan*/ *,int*,int) ; 
 char* obs_encoder_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_output_get_audio_encoder (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  set_output_error (struct rtmp_stream*) ; 
 int /*<<< orphan*/  set_rtmp_dstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  win32_log_interface_type (struct rtmp_stream*) ; 

__attribute__((used)) static int try_connect(struct rtmp_stream *stream)
{
	if (dstr_is_empty(&stream->path)) {
		warn("URL is empty");
		return OBS_OUTPUT_BAD_PATH;
	}

	info("Connecting to RTMP URL %s...", stream->path.array);

	RTMP_Init(&stream->rtmp);
	if (!RTMP_SetupURL(&stream->rtmp, stream->path.array))
		return OBS_OUTPUT_BAD_PATH;

	RTMP_EnableWrite(&stream->rtmp);

	dstr_copy(&stream->encoder_name, "FMLE/3.0 (compatible; FMSc/1.0)");

	set_rtmp_dstr(&stream->rtmp.Link.pubUser, &stream->username);
	set_rtmp_dstr(&stream->rtmp.Link.pubPasswd, &stream->password);
	set_rtmp_dstr(&stream->rtmp.Link.flashVer, &stream->encoder_name);
	stream->rtmp.Link.swfUrl = stream->rtmp.Link.tcUrl;

	if (dstr_is_empty(&stream->bind_ip) ||
	    dstr_cmp(&stream->bind_ip, "default") == 0) {
		memset(&stream->rtmp.m_bindIP, 0,
		       sizeof(stream->rtmp.m_bindIP));
	} else {
		bool success = netif_str_to_addr(&stream->rtmp.m_bindIP.addr,
						 &stream->rtmp.m_bindIP.addrLen,
						 stream->bind_ip.array);
		if (success) {
			int len = stream->rtmp.m_bindIP.addrLen;
			bool ipv6 = len == sizeof(struct sockaddr_in6);
			info("Binding to IPv%d", ipv6 ? 6 : 4);
		}
	}

	RTMP_AddStream(&stream->rtmp, stream->key.array);

	for (size_t idx = 1;; idx++) {
		obs_encoder_t *encoder =
			obs_output_get_audio_encoder(stream->output, idx);
		const char *encoder_name;

		if (!encoder)
			break;

		encoder_name = obs_encoder_get_name(encoder);
		RTMP_AddStream(&stream->rtmp, encoder_name);
	}

	stream->rtmp.m_outChunkSize = 4096;
	stream->rtmp.m_bSendChunkSizeInfo = true;
	stream->rtmp.m_bUseNagle = true;

#ifdef _WIN32
	win32_log_interface_type(stream);
#endif

	if (!RTMP_Connect(&stream->rtmp, NULL)) {
		set_output_error(stream);
		return OBS_OUTPUT_CONNECT_FAILED;
	}

	if (!RTMP_ConnectStream(&stream->rtmp, 0))
		return OBS_OUTPUT_INVALID_STREAM;

	info("Connection to %s successful", stream->path.array);

	return init_send(stream);
}