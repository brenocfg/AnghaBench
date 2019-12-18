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
struct TYPE_3__ {int /*<<< orphan*/  sb_socket; } ;
struct TYPE_4__ {TYPE_1__ m_sb; } ;
struct rtmp_stream {TYPE_2__ rtmp; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void adjust_sndbuf_size(struct rtmp_stream *stream, int new_size)
{
	int cur_sendbuf_size = new_size;
	socklen_t int_size = sizeof(int);

	getsockopt(stream->rtmp.m_sb.sb_socket, SOL_SOCKET, SO_SNDBUF,
		   (char *)&cur_sendbuf_size, &int_size);

	if (cur_sendbuf_size < new_size) {
		cur_sendbuf_size = new_size;
		setsockopt(stream->rtmp.m_sb.sb_socket, SOL_SOCKET, SO_SNDBUF,
			   (const char *)&cur_sendbuf_size, int_size);
	}
}