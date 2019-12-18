#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_3__ {int /*<<< orphan*/  sb_socket; } ;
struct TYPE_4__ {TYPE_1__ m_sb; } ;
struct rtmp_stream {size_t total_bytes_sent; TYPE_2__ rtmp; int /*<<< orphan*/  start_dts_offset; int /*<<< orphan*/  new_socket_loop; } ;
struct encoder_packet {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIONREAD ; 
 int RTMP_Write (TYPE_2__*,char*,int,int) ; 
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  discard_recv_data (struct rtmp_stream*,size_t) ; 
 int /*<<< orphan*/  droptest_cap_data_rate (struct rtmp_stream*,size_t) ; 
 int /*<<< orphan*/  flv_packet_mux (struct encoder_packet*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*,int) ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int ioctlsocket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_encoder_packet_release (struct encoder_packet*) ; 

__attribute__((used)) static int send_packet(struct rtmp_stream *stream,
		       struct encoder_packet *packet, bool is_header,
		       size_t idx)
{
	uint8_t *data;
	size_t size;
	int recv_size = 0;
	int ret = 0;

	if (!stream->new_socket_loop) {
#ifdef _WIN32
		ret = ioctlsocket(stream->rtmp.m_sb.sb_socket, FIONREAD,
				  (u_long *)&recv_size);
#else
		ret = ioctl(stream->rtmp.m_sb.sb_socket, FIONREAD, &recv_size);
#endif

		if (ret >= 0 && recv_size > 0) {
			if (!discard_recv_data(stream, (size_t)recv_size))
				return -1;
		}
	}

	flv_packet_mux(packet, is_header ? 0 : stream->start_dts_offset, &data,
		       &size, is_header);

#ifdef TEST_FRAMEDROPS
	droptest_cap_data_rate(stream, size);
#endif

	ret = RTMP_Write(&stream->rtmp, (char *)data, (int)size, (int)idx);
	bfree(data);

	if (is_header)
		bfree(packet->data);
	else
		obs_encoder_packet_release(packet);

	stream->total_bytes_sent += size;
	return ret;
}