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
typedef  int /*<<< orphan*/  Port ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_retry_write (int /*<<< orphan*/ *) ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 scalar_t__ errno ; 
 int secure_raw_write (int /*<<< orphan*/ *,char const*,int) ; 

__attribute__((used)) static int
my_sock_write(BIO *h, const char *buf, int size)
{
	int			res = 0;

	res = secure_raw_write(((Port *) BIO_get_data(h)), buf, size);
	BIO_clear_retry_flags(h);
	if (res <= 0)
	{
		/* If we were interrupted, tell caller to retry */
		if (errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)
		{
			BIO_set_retry_write(h);
		}
	}

	return res;
}