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
typedef  int /*<<< orphan*/  PGconn ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_retry_read (int /*<<< orphan*/ *) ; 
#define  EAGAIN 130 
#define  EINTR 129 
#define  EWOULDBLOCK 128 
 int SOCK_ERRNO ; 
 int pqsecure_raw_read (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
my_sock_read(BIO *h, char *buf, int size)
{
	int			res;

	res = pqsecure_raw_read((PGconn *) BIO_get_data(h), buf, size);
	BIO_clear_retry_flags(h);
	if (res < 0)
	{
		/* If we were interrupted, tell caller to retry */
		switch (SOCK_ERRNO)
		{
#ifdef EAGAIN
			case EAGAIN:
#endif
#if defined(EWOULDBLOCK) && (!defined(EAGAIN) || (EWOULDBLOCK != EAGAIN))
			case EWOULDBLOCK:
#endif
			case EINTR:
				BIO_set_retry_read(h);
				break;

			default:
				break;
		}
	}

	return res;
}