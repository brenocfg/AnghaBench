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

/* Variables and functions */
 int /*<<< orphan*/  ZEND_STRL (char*) ; 
 char* emalloc (int) ; 
 char* erealloc (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static int phpdbg_encode_xml(char **buf, char *msg, int msglen, int from, char *to) {
	int i;
	int tolen = to ? strlen(to) : 5;
	char *tmp = *buf = emalloc(msglen * tolen);
	for (i = 0; i++ < msglen; msg++) {
		if (*msg == '&') {
			memcpy(tmp, ZEND_STRL("&amp;"));
			tmp += sizeof("&amp;") - 1;
		} else if (*msg == '<') {
			memcpy(tmp, ZEND_STRL("&lt;"));
			tmp += sizeof("&lt;") - 1;
		} else if (((int) *msg) == from) {
			memcpy(tmp, to, tolen);
			tmp += tolen;
		} else {
			*tmp++ = *msg;
		}
	}

	{
		int len = tmp - *buf;
		*buf = erealloc(*buf, len + 1);
		return len;
	}
}