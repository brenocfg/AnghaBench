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
typedef  scalar_t__ zend_off_t ;
typedef  int ssize_t ;
struct TYPE_3__ {size_t i_len; int i_fd; int /*<<< orphan*/ * i_buf; } ;
typedef  TYPE_1__ cdf_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ FINFO_LSEEK_FUNC (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int FINFO_READ_FUNC (int,void*,size_t) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ssize_t
cdf_read(const cdf_info_t *info, zend_off_t off, void *buf, size_t len)
{
	size_t siz = (size_t)off + len;

	if ((zend_off_t)(off + len) != (zend_off_t)siz) {
		goto out;
	}

	if (info->i_buf != NULL && info->i_len >= siz) {
		(void)memcpy(buf, &info->i_buf[off], len);
		return (ssize_t)len;
	}

	if (info->i_fd == -1)
		goto out;

	if (FINFO_LSEEK_FUNC(info->i_fd, off, SEEK_SET) == (zend_off_t)-1)
		return -1;

	if (FINFO_READ_FUNC(info->i_fd, buf, len) != (ssize_t)len)
		return -1;

	return (ssize_t)len;
out:
	errno = EINVAL;
	return -1;
}