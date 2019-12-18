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
struct TYPE_3__ {int /*<<< orphan*/  sb_socket; } ;
struct TYPE_4__ {TYPE_1__ m_sb; } ;
struct rtmp_stream {TYPE_2__ rtmp; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  TYPE_2__ RTMP ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int WSAGetLastError () ; 
 int /*<<< orphan*/  do_log (int /*<<< orphan*/ ,char*,int,int) ; 
 int errno ; 
 int /*<<< orphan*/  recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool discard_recv_data(struct rtmp_stream *stream, size_t size)
{
	RTMP *rtmp = &stream->rtmp;
	uint8_t buf[512];
#ifdef _WIN32
	int ret;
#else
	ssize_t ret;
#endif

	do {
		size_t bytes = size > 512 ? 512 : size;
		size -= bytes;

#ifdef _WIN32
		ret = recv(rtmp->m_sb.sb_socket, buf, (int)bytes, 0);
#else
		ret = recv(rtmp->m_sb.sb_socket, buf, bytes, 0);
#endif

		if (ret <= 0) {
#ifdef _WIN32
			int error = WSAGetLastError();
#else
			int error = errno;
#endif
			if (ret < 0) {
				do_log(LOG_ERROR, "recv error: %d (%d bytes)",
				       error, (int)size);
			}
			return false;
		}
	} while (size > 0);

	return true;
}