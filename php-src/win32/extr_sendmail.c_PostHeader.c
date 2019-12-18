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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAIL_BUFFER_SIZE ; 
 int OUT_OF_MEMORY ; 
 int Post (char*) ; 
 int SUCCESS ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addToHeader (char**,char*,char*) ; 
 char* ecalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* estrdup (char*) ; 
 int /*<<< orphan*/ * php_format_date (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strstr (char*,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 char tolower (char) ; 
 int /*<<< orphan*/  zend_string_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int PostHeader(char *RPath, char *Subject, char *mailTo, char *xheaders)
{
	/* Print message header according to RFC 822 */
	/* Return-path, Received, Date, From, Subject, Sender, To, cc */

	int res;
	char *header_buffer;
	char *headers_lc = NULL;
	size_t i;

	if (xheaders) {
		size_t headers_lc_len;

		headers_lc = estrdup(xheaders);
		headers_lc_len = strlen(headers_lc);

		for (i = 0; i < headers_lc_len; i++) {
			headers_lc[i] = tolower(headers_lc[i]);
		}
	}

	header_buffer = ecalloc(1, MAIL_BUFFER_SIZE);

	if (!xheaders || !strstr(headers_lc, "date:")) {
		time_t tNow = time(NULL);
		zend_string *dt = php_format_date("r", 1, tNow, 1);

		snprintf(header_buffer, MAIL_BUFFER_SIZE, "Date: %s\r\n", ZSTR_VAL(dt));
		zend_string_free(dt);
	}

	if (!headers_lc || !strstr(headers_lc, "from:")) {
		if (!addToHeader(&header_buffer, "From: %s\r\n", RPath)) {
			goto PostHeader_outofmem;
		}
	}
	if (!addToHeader(&header_buffer, "Subject: %s\r\n", Subject)) {
		goto PostHeader_outofmem;
	}

	/* Only add the To: field from the $to parameter if isn't in the custom headers */
	if ((headers_lc && (!strstr(headers_lc, "\r\nto:") && (strncmp(headers_lc, "to:", 3) != 0))) || !headers_lc) {
		if (!addToHeader(&header_buffer, "To: %s\r\n", mailTo)) {
			goto PostHeader_outofmem;
		}
	}
	if (xheaders) {
		if (!addToHeader(&header_buffer, "%s\r\n", xheaders)) {
			goto PostHeader_outofmem;
		}
	}

	if (headers_lc) {
		efree(headers_lc);
	}
	if ((res = Post(header_buffer)) != SUCCESS) {
		efree(header_buffer);
		return (res);
	}
	efree(header_buffer);

	if ((res = Post("\r\n")) != SUCCESS) {
		return (res);
	}

	return (SUCCESS);

PostHeader_outofmem:
	if (headers_lc) {
		efree(headers_lc);
	}
	return OUT_OF_MEMORY;
}