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
typedef  int /*<<< orphan*/  zend_uchar ;
typedef  int /*<<< orphan*/  enum_func_status ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL ; 
 int /*<<< orphan*/  PASS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  mnd_efree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mnd_emalloc (size_t) ; 

__attribute__((used)) static enum_func_status
mysqlnd_stmt_execute_check_n_enlarge_buffer(zend_uchar **buf, zend_uchar **p, size_t * buf_len, zend_uchar * const provided_buffer, size_t needed_bytes)
{
	const size_t overalloc = 5;
	size_t left = (*buf_len - (*p - *buf));

	if (left < (needed_bytes + overalloc)) {
		const size_t offset = *p - *buf;
		zend_uchar *tmp_buf;
		*buf_len = offset + needed_bytes + overalloc;
		tmp_buf = mnd_emalloc(*buf_len);
		if (!tmp_buf) {
			return FAIL;
		}
		memcpy(tmp_buf, *buf, offset);
		if (*buf != provided_buffer) {
			mnd_efree(*buf);
		}
		*buf = tmp_buf;
		/* Update our pos pointer */
		*p = *buf + offset;
	}
	return PASS;
}