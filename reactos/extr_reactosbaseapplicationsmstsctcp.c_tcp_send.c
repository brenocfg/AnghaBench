#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int end; int data; } ;
typedef  TYPE_1__* STREAM ;

/* Variables and functions */
 scalar_t__ TCP_BLOCKS ; 
 int /*<<< orphan*/  TCP_SLEEP (int /*<<< orphan*/ ) ; 
 char* TCP_STRERROR ; 
 scalar_t__ True ; 
 int /*<<< orphan*/  error (char*,int,char*) ; 
 scalar_t__ g_network_error ; 
 int /*<<< orphan*/  g_sock ; 
 int send (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 

void
tcp_send(STREAM s)
{
	int length = s->end - s->data;
	int sent, total = 0;

	if (g_network_error == True)
		return;

#ifdef WITH_SCARD
	scard_lock(SCARD_LOCK_TCP);
#endif
	while (total < length)
	{
#ifdef WITH_SSL
		if (g_ssl)
		{
			const BYTE *ptr = s->data + total;
			size_t chunk_size;

			sent = 0;

			while (length - total)
			{
				chunk_size = min(length - total, g_ssl->ssl_sizes.cbMaximumMessage);
				if (!send_ssl_chunk(ptr, chunk_size))
				{
#ifdef WITH_SCARD
					scard_unlock(SCARD_LOCK_TCP);
#endif

					//error("send_ssl_chunk: %d (%s)\n", sent, TCP_STRERROR);
					g_network_error = True;
					return;
				}

				sent += chunk_size;
				ptr += chunk_size;
				length -= chunk_size;
			}
		}
		else
		{
#endif /* WITH_SSL */
			sent = send(g_sock, (const char *)s->data + total, length - total, 0);
			if (sent <= 0)
			{
				if (sent == -1 && TCP_BLOCKS)
				{
					TCP_SLEEP(0);
					sent = 0;
				}
				else
				{
#ifdef WITH_SCARD
					scard_unlock(SCARD_LOCK_TCP);
#endif

					error("send: %d (%s)\n", sent, TCP_STRERROR);
					g_network_error = True;
					return;
				}
			}
#ifdef WITH_SSL
		}
#endif /* WITH_SSL */
		total += sent;
	}
#ifdef WITH_SCARD
	scard_unlock(SCARD_LOCK_TCP);
#endif
}