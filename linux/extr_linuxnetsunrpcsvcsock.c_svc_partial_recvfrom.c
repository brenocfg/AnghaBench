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
struct svc_rqst {int dummy; } ;
struct kvec {unsigned int iov_len; void* iov_base; } ;

/* Variables and functions */
 int svc_recvfrom (struct svc_rqst*,struct kvec*,int,int) ; 

__attribute__((used)) static int svc_partial_recvfrom(struct svc_rqst *rqstp,
				struct kvec *iov, int nr,
				int buflen, unsigned int base)
{
	size_t save_iovlen;
	void *save_iovbase;
	unsigned int i;
	int ret;

	if (base == 0)
		return svc_recvfrom(rqstp, iov, nr, buflen);

	for (i = 0; i < nr; i++) {
		if (iov[i].iov_len > base)
			break;
		base -= iov[i].iov_len;
	}
	save_iovlen = iov[i].iov_len;
	save_iovbase = iov[i].iov_base;
	iov[i].iov_len -= base;
	iov[i].iov_base += base;
	ret = svc_recvfrom(rqstp, &iov[i], nr - i, buflen);
	iov[i].iov_len = save_iovlen;
	iov[i].iov_base = save_iovbase;
	return ret;
}