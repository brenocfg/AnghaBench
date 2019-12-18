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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  php_stream ;
typedef  int /*<<< orphan*/  markername ;

/* Variables and functions */
 int M_APP0 ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_assoc_stringl (int /*<<< orphan*/ *,char*,char*,unsigned short) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (size_t) ; 
 unsigned short php_read2 (int /*<<< orphan*/ *) ; 
 unsigned short php_stream_read (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/ * zend_hash_str_find (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int php_read_APP(php_stream * stream, unsigned int marker, zval *info)
{
	unsigned short length;
	char *buffer;
	char markername[16];
	zval *tmp;

	length = php_read2(stream);
	if (length < 2)	{
		return 0;
	}
	length -= 2;				/* length includes itself */

	buffer = emalloc((size_t)length);

	if (php_stream_read(stream, buffer, (size_t) length) != length) {
		efree(buffer);
		return 0;
	}

	snprintf(markername, sizeof(markername), "APP%d", marker - M_APP0);

	if ((tmp = zend_hash_str_find(Z_ARRVAL_P(info), markername, strlen(markername))) == NULL) {
		/* XXX we only catch the 1st tag of it's kind! */
		add_assoc_stringl(info, markername, buffer, length);
	}

	efree(buffer);
	return 1;
}