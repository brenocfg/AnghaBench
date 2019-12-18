#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_13__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  s; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ smart_str ;
struct TYPE_20__ {int /*<<< orphan*/  buffer; } ;
struct TYPE_21__ {int /*<<< orphan*/  st_size; } ;
struct TYPE_22__ {char* path_translated; int path_translated_len; TYPE_1__ sb; int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  ext_len; int /*<<< orphan*/  ext; } ;
struct TYPE_24__ {int content_sender_initialized; int file_fd; int /*<<< orphan*/  sock; TYPE_13__ content_sender; TYPE_2__ request; } ;
typedef  TYPE_4__ php_cli_server_client ;
typedef  int /*<<< orphan*/  php_cli_server_chunk ;
struct TYPE_25__ {int /*<<< orphan*/  poller; } ;
typedef  TYPE_5__ php_cli_server ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  POLLOUT ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_essential_headers (TYPE_3__*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  append_http_status_line (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 char* get_mime_type (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_cli_server_buffer_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * php_cli_server_chunk_heap_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_cli_server_content_sender_ctor (TYPE_13__*) ; 
 int /*<<< orphan*/  php_cli_server_log_response (TYPE_4__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_cli_server_poller_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int php_cli_server_send_error_page (TYPE_5__*,TYPE_4__*,int) ; 
 int php_win32_ioutil_open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_append_unsigned_ex (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smart_str_appendl_ex (TYPE_3__*,char*,int,int) ; 
 int /*<<< orphan*/  smart_str_appends_ex (TYPE_3__*,char const*,int) ; 
 int /*<<< orphan*/  smart_str_free_ex (TYPE_3__*,int) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int php_cli_server_begin_send_static(php_cli_server *server, php_cli_server_client *client) /* {{{ */
{
	int fd;
	int status = 200;

	if (client->request.path_translated && strlen(client->request.path_translated) != client->request.path_translated_len) {
		/* can't handle paths that contain nul bytes */
		return php_cli_server_send_error_page(server, client, 400);
	}

#ifdef PHP_WIN32
	/* The win32 namespace will cut off trailing dots and spaces. Since the
	   VCWD functionality isn't used here, a sophisticated functionality
	   would have to be reimplemented to know ahead there are no files
	   with invalid names there. The simplest is just to forbid invalid
	   filenames, which is done here. */
	if (client->request.path_translated &&
		('.' == client->request.path_translated[client->request.path_translated_len-1] ||
		 ' ' == client->request.path_translated[client->request.path_translated_len-1])) {
		return php_cli_server_send_error_page(server, client, 500);
	}

	fd = client->request.path_translated ? php_win32_ioutil_open(client->request.path_translated, O_RDONLY): -1;
#else
	fd = client->request.path_translated ? open(client->request.path_translated, O_RDONLY): -1;
#endif
	if (fd < 0) {
		return php_cli_server_send_error_page(server, client, 404);
	}

	php_cli_server_content_sender_ctor(&client->content_sender);
	client->content_sender_initialized = 1;
	client->file_fd = fd;

	{
		php_cli_server_chunk *chunk;
		smart_str buffer = { 0 };
		const char *mime_type = get_mime_type(server, client->request.ext, client->request.ext_len);

		append_http_status_line(&buffer, client->request.protocol_version, status, 1);
		if (!buffer.s) {
			/* out of memory */
			php_cli_server_log_response(client, 500, NULL);
			return FAILURE;
		}
		append_essential_headers(&buffer, client, 1);
		if (mime_type) {
			smart_str_appendl_ex(&buffer, "Content-Type: ", sizeof("Content-Type: ") - 1, 1);
			smart_str_appends_ex(&buffer, mime_type, 1);
			if (strncmp(mime_type, "text/", 5) == 0) {
				smart_str_appends_ex(&buffer, "; charset=UTF-8", 1);
			}
			smart_str_appendl_ex(&buffer, "\r\n", 2, 1);
		}
		smart_str_appends_ex(&buffer, "Content-Length: ", 1);
		smart_str_append_unsigned_ex(&buffer, client->request.sb.st_size, 1);
		smart_str_appendl_ex(&buffer, "\r\n", 2, 1);
		smart_str_appendl_ex(&buffer, "\r\n", 2, 1);
		chunk = php_cli_server_chunk_heap_new(buffer.s, ZSTR_VAL(buffer.s), ZSTR_LEN(buffer.s));
		if (!chunk) {
			smart_str_free_ex(&buffer, 1);
			php_cli_server_log_response(client, 500, NULL);
			return FAILURE;
		}
		php_cli_server_buffer_append(&client->content_sender.buffer, chunk);
	}
	php_cli_server_log_response(client, 200, NULL);
	php_cli_server_poller_add(&server->poller, POLLOUT, client->sock);
	return SUCCESS;
}