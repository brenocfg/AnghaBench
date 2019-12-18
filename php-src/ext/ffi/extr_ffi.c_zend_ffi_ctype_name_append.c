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
struct TYPE_3__ {scalar_t__ end; scalar_t__ buf; } ;
typedef  TYPE_1__ zend_ffi_ctype_name_buf ;

/* Variables and functions */
 scalar_t__ MAX_TYPE_NAME_LEN ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,size_t) ; 

__attribute__((used)) static int zend_ffi_ctype_name_append(zend_ffi_ctype_name_buf *buf, const char *str, size_t len) /* {{{ */
{
	if (buf->end + len > buf->buf + MAX_TYPE_NAME_LEN) {
		return 0;
	}
	memcpy(buf->end, str, len);
	buf->end += len;
	return 1;
}