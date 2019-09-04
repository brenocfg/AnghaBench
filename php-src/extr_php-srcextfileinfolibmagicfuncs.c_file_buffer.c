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
struct magic_set {int flags; } ;
struct buffer {int dummy; } ;
typedef  int /*<<< orphan*/  php_stream ;

/* Variables and functions */
 int /*<<< orphan*/  BINTEST ; 
 int MAGIC_APPLE ; 
 int MAGIC_DEBUG ; 
 int MAGIC_EXTENSION ; 
 int MAGIC_MIME ; 
 int MAGIC_MIME_ENCODING ; 
 int MAGIC_MIME_TYPE ; 
 int MAGIC_NO_CHECK_CDF ; 
 int MAGIC_NO_CHECK_ENCODING ; 
 int MAGIC_NO_CHECK_SOFT ; 
 int MAGIC_NO_CHECK_TAR ; 
 int MAGIC_NO_CHECK_TEXT ; 
 int /*<<< orphan*/  PHP_STREAM_AS_FD ; 
 int SUCCESS ; 
 int /*<<< orphan*/  buffer_fini (struct buffer*) ; 
 int /*<<< orphan*/  buffer_init (struct buffer*,int,void const*,size_t) ; 
 scalar_t__ checkdone (struct magic_set*,int*) ; 
 int file_ascmagic (struct magic_set*,struct buffer*,int) ; 
 int file_encoding (struct magic_set*,struct buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,char const**,char const**) ; 
 int file_is_tar (struct magic_set*,struct buffer*) ; 
 int file_printf (struct magic_set*,char*,...) ; 
 int file_softmagic (struct magic_set*,struct buffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int file_trycdf (struct magic_set*,struct buffer*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int php_stream_cast (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int
file_buffer(struct magic_set *ms, php_stream *stream, const char *inname, const void *buf,
    size_t nb)
{
	int m = 0, rv = 0, looks_text = 0;
	const char *code = NULL;
	const char *code_mime = "binary";
	const char *type = "application/octet-stream";
	const char *def = "data";
	const char *ftype = NULL;
	struct buffer b;
	int fd = -1;
	
	buffer_init(&b, fd, buf, nb);

	if (nb == 0) {
		def = "empty";
		type = "application/x-empty";
		goto simple;
	} else if (nb == 1) {
		def = "very short file (no magic)";
		goto simple;
	}

	if ((ms->flags & MAGIC_NO_CHECK_ENCODING) == 0) {
		looks_text = file_encoding(ms, &b, NULL, 0,
		    &code, &code_mime, &ftype);
	}

#ifdef __EMX__
	if ((ms->flags & MAGIC_NO_CHECK_APPTYPE) == 0 && inname) {
		m = file_os2_apptype(ms, inname, &b);
		if ((ms->flags & MAGIC_DEBUG) != 0)
			(void)fprintf(stderr, "[try os2_apptype %d]\n", m);
		switch (m) {
		case -1:
			return -1;
		case 0:
			break;
		default:
			return 1;
		}
	}
#endif

#if PHP_FILEINFO_UNCOMPRESS
	if ((ms->flags & MAGIC_NO_CHECK_COMPRESS) == 0) {
		m = file_zmagic(ms, &b, inname);
		if ((ms->flags & MAGIC_DEBUG) != 0)
			(void)fprintf(stderr, "[try zmagic %d]\n", m);
		if (m) {
			goto done_encoding;
		}
	}
#endif
	/* Check if we have a tar file */
	if ((ms->flags & MAGIC_NO_CHECK_TAR) == 0) {
		m = file_is_tar(ms, &b);
		if ((ms->flags & MAGIC_DEBUG) != 0)
			(void)fprintf(stderr, "[try tar %d]\n", m);
		if (m) {
			if (checkdone(ms, &rv))
				goto done;
		}
	}

	/* Check if we have a CDF file */
	if ((ms->flags & MAGIC_NO_CHECK_CDF) == 0 && stream) {
#ifdef _WIN64
		php_socket_t _fd = fd;
		int _ret = php_stream_cast(stream, PHP_STREAM_AS_FD, (void **)&_fd, 0);
		fd = (int)_fd;
#else
		int _ret = php_stream_cast(stream, PHP_STREAM_AS_FD, (void **)&fd, 0);
#endif
		if (SUCCESS == _ret) {
			m = file_trycdf(ms, &b);
			if ((ms->flags & MAGIC_DEBUG) != 0)
				(void)fprintf(stderr, "[try cdf %d]\n", m);
			if (m) {
				if (checkdone(ms, &rv))
					goto done;
			}
		}
	}

	/* try soft magic tests */
	if ((ms->flags & MAGIC_NO_CHECK_SOFT) == 0) {
		m = file_softmagic(ms, &b, NULL, NULL, BINTEST, looks_text);
		if ((ms->flags & MAGIC_DEBUG) != 0)
			(void)fprintf(stderr, "[try softmagic %d]\n", m);
		if (m) {
#ifdef BUILTIN_ELF
			if ((ms->flags & MAGIC_NO_CHECK_ELF) == 0 && m == 1 &&
			    nb > 5 && fd != -1) {
				/*
				 * We matched something in the file, so this
				 * *might* be an ELF file, and the file is at
				 * least 5 bytes long, so if it's an ELF file
				 * it has at least one byte past the ELF magic
				 * number - try extracting information from the
				 * ELF headers that cannot easily * be
				 * extracted with rules in the magic file.
				 */
				m = file_tryelf(ms, &b);
				if ((ms->flags & MAGIC_DEBUG) != 0)
					(void)fprintf(stderr, "[try elf %d]\n",
					    m);
			}
#endif
			if (checkdone(ms, &rv))
				goto done;
		}
	}

	/* try text properties */
	if ((ms->flags & MAGIC_NO_CHECK_TEXT) == 0) {

		m = file_ascmagic(ms, &b, looks_text);
		if ((ms->flags & MAGIC_DEBUG) != 0)
			(void)fprintf(stderr, "[try ascmagic %d]\n", m);
		if (m) {
			if (checkdone(ms, &rv))
				goto done;
		}
	}

simple:
	/* give up */
	m = 1;
	if (ms->flags & MAGIC_MIME) {
		if ((ms->flags & MAGIC_MIME_TYPE) &&
		    file_printf(ms, "%s", type) == -1)
			rv = -1;
	} else if (ms->flags & MAGIC_APPLE) {
		if (file_printf(ms, "UNKNUNKN") == -1)
			rv = -1;
	} else if (ms->flags & MAGIC_EXTENSION) {
		if (file_printf(ms, "???") == -1)
			rv = -1;
	} else {
		if (file_printf(ms, "%s", def) == -1)
			rv = -1;
	}
 done:
	if ((ms->flags & MAGIC_MIME_ENCODING) != 0) {
		if (ms->flags & MAGIC_MIME_TYPE)
			if (file_printf(ms, "; charset=") == -1)
				rv = -1;
		if (file_printf(ms, "%s", code_mime) == -1)
			rv = -1;
	}
#if PHP_FILEINFO_UNCOMPRESS
 done_encoding:
#endif
	buffer_fini(&b);
	if (rv)
		return rv;

	return m;
}