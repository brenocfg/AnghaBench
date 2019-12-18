#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* wrapper; } ;
typedef  TYPE_2__ php_stream ;
typedef  int /*<<< orphan*/  X509_STORE ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_6__ {scalar_t__ is_url; } ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_puts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  E_WARNING ; 
 int /*<<< orphan*/ * PEM_read_bio_X509 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ X509_STORE_add_cert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  php_error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  php_stream_close (TYPE_2__*) ; 
 char* php_stream_get_line (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 
 TYPE_2__* php_stream_open_wrapper (char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static long php_openssl_load_stream_cafile(X509_STORE *cert_store, const char *cafile) /* {{{ */
{
	php_stream *stream;
	X509 *cert;
	BIO *buffer;
	int buffer_active = 0;
	char *line = NULL;
	size_t line_len;
	long certs_added = 0;

	stream = php_stream_open_wrapper(cafile, "rb", 0, NULL);

	if (stream == NULL) {
		php_error(E_WARNING, "failed loading cafile stream: `%s'", cafile);
		return 0;
	} else if (stream->wrapper->is_url) {
		php_stream_close(stream);
		php_error(E_WARNING, "remote cafile streams are disabled for security purposes");
		return 0;
	}

	cert_start: {
		line = php_stream_get_line(stream, NULL, 0, &line_len);
		if (line == NULL) {
			goto stream_complete;
		} else if (!strcmp(line, "-----BEGIN CERTIFICATE-----\n") ||
			!strcmp(line, "-----BEGIN CERTIFICATE-----\r\n")
		) {
			buffer = BIO_new(BIO_s_mem());
			buffer_active = 1;
			goto cert_line;
		} else {
			efree(line);
			goto cert_start;
		}
	}

	cert_line: {
		BIO_puts(buffer, line);
		efree(line);
		line = php_stream_get_line(stream, NULL, 0, &line_len);
		if (line == NULL) {
			goto stream_complete;
		} else if (!strcmp(line, "-----END CERTIFICATE-----") ||
			!strcmp(line, "-----END CERTIFICATE-----\n") ||
			!strcmp(line, "-----END CERTIFICATE-----\r\n")
		) {
			goto add_cert;
		} else {
			goto cert_line;
		}
	}

	add_cert: {
		BIO_puts(buffer, line);
		efree(line);
		cert = PEM_read_bio_X509(buffer, NULL, 0, NULL);
		BIO_free(buffer);
		buffer_active = 0;
		if (cert && X509_STORE_add_cert(cert_store, cert)) {
			++certs_added;
			X509_free(cert);
		}
		goto cert_start;
	}

	stream_complete: {
		php_stream_close(stream);
		if (buffer_active == 1) {
			BIO_free(buffer);
		}
	}

	if (certs_added == 0) {
		php_error(E_WARNING, "no valid certs found cafile stream: `%s'", cafile);
	}

	return certs_added;
}